#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>
#include <arpa/inet.h> //支持struct sockaddr_in
#include <sys/socket.h>
#include <sys/un.h>
#define CLIENT_COUNT 1280
#define SIZE 128
typedef struct
{
    char address[32];
    int fd;
    char user[32];
} tcpClient;

// 客户端状态
typedef struct
{
    char address[32];
    int status;
} tcpClientStatus;

tcpClient *initTcpClient(char *address, int fd)
{
    tcpClient *client = (tcpClient *)malloc(sizeof(tcpClient));
    if (client)
    {
        bzero(client, sizeof(tcpClient));
        sprintf(client->address, "%s", address);
        client->fd = fd;
        return client;
    }
    return NULL;
}

// void *readClientDatas(void *args);

int main()
{
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        perror("socket失败");
        return 0;
    }
    fprintf(stderr, "socket成功  fd=%d\n", serverFd);

    // 端口可复用
    int rUseAddr = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &rUseAddr, sizeof(rUseAddr));

    // 设置监听器为非阻塞模式
    int val = fcntl(serverFd, F_GETFL);
    val |= O_NONBLOCK;
    fcntl(serverFd, F_SETFL, val);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9000);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t len = sizeof(serverAddress);
    // int bind(int __fd, const struct sockaddr *__addr, socklen_t __len)
    if (bind(serverFd, (struct sockaddr *)&serverAddress, len))
    {
        perror("bind失败");
        return 0;
    }
    fprintf(stderr, "bind成功\n");

    if (listen(serverFd, 10))
    {
        perror("listen失败");
        return 0;
    }

    fprintf(stderr, "服务器启动 监听 0.0.0.0:%d \n", ntohs(serverAddress.sin_port));

    // 准备共享内存，向内存中更新上线信息
    key_t shmKey = ftok(".", 1009);
    if (shmKey == -1)
    {
        perror("ftok失败");
        return 0;
    }
    int shmID = shmget(shmKey, SIZE, IPC_CREAT | 0664);
    if (shmID == -1)
    {
        perror("shmID失败");
        return 0;
    }
    tcpClientStatus *clientStatus = shmat(shmID, NULL, 0);
    if (clientStatus == NULL)
    {
        perror("shmat失败");
        return 0;
    }

    // 管理所有socket的数组
    tcpClient *clientArray[CLIENT_COUNT] = {NULL};
    bzero(clientArray, sizeof(tcpClient*) * CLIENT_COUNT);
    int currentClientCount = 0;

    struct sockaddr_in peerAddress;
    char addressInfo[32] = "\0";
    int newFd;
    tcpClientStatus newClientStatus;
    int tempClientCount = -1;

    // 线程轮巡
    while (1)
    {
        // 检查是否有新的连接
        newFd = accept(serverFd, (struct sockaddr *)&peerAddress, &len);
        if (newFd > 0)
        {
            fprintf(stderr, "有新的客户端链接 %s:%d\n", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
            bzero(addressInfo, sizeof(addressInfo));
            sprintf(addressInfo, "%s:%d", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
            // 初始化新的客户端  传给服务线程使用(创建1个Fd给新的客户端)
            tcpClient *newClient = initTcpClient(addressInfo, newFd);
            clientArray[currentClientCount] = newClient;
            currentClientCount++;

            // 设置新的客户端SOCKEY为非阻塞模式
            int val = fcntl(newClient->fd, F_GETFL);
            val |= O_NONBLOCK;
            fcntl(newClient->fd, F_SETFL, val);

            // 清理现有的客户端状态临时空间
            bzero(&newClientStatus, sizeof(newClientStatus));
            // 保存新的客户端状态信息
            strcpy(newClientStatus.address, addressInfo);
            newClientStatus.status = 1;       
            // 清理共享内存
            bzero(clientStatus,sizeof(clientStatus));
            // 拷贝新的客户端状态到共享内存
            memcpy(clientStatus, &newClientStatus, sizeof(newClientStatus));
            fprintf(stderr, "已发送新的客户端%s上线信息到共享内存\n", clientStatus->address);
        }

        // 遍历所有客户端看是否有新数据
        for (int i = 0; i < currentClientCount; i++)
        {
            tcpClient *currentClient = clientArray[i];

            char buf[SIZE] = "\0";
            char recvOk[SIZE] = "\0";
            int index = 0;

            if (read(currentClient->fd, buf, SIZE) > 0)
            {
                fprintf(stderr, "%s说:%s\n", currentClient->address, buf);
                // 0#hello#789383
                int num, value;
                sscanf(buf, "%d#hello#%d", &num, &value);
                fprintf(stderr, "\t\t收到%s的[%d]消息\n", currentClient->address, num);
                bzero(recvOk, SIZE);
                sprintf(recvOk, "%d#OK #", num);
                if (write(currentClient->fd, recvOk, strlen(recvOk)) > 0)
                {
                    fprintf(stderr, "\t\t%s的[%d]消息已回复OK\n", currentClient->address, num);
                }
                bzero(buf, SIZE);
            }
        }
    }
}


/*
    void *readClientDatas(void *args)
    {
        if (args == NULL)
        {
            return NULL;
        }
        fprintf(stderr, "客户端线程%ld启动\n", pthread_self());
        tcpClient *currentClient = (tcpClient *)args;

        char buf[SIZE] = "\0";
        char recvOk[SIZE] = "\0";
        int index = 0;
        while (1)
        {
            if (read(currentClient->fd, buf, SIZE) > 0)
            {
                fprintf(stderr, "%s说:%s\n", currentClient->address, buf);
                // 0#hello#789383
                int num, value;
                sscanf(buf, "%d#hello#%d", &num, &value);
                fprintf(stderr, "\t\t收到%s的[%d]消息\n", currentClient->address, num);
                bzero(recvOk, SIZE);
                sprintf(recvOk, "%d#OK #", num);
                if (write(currentClient->fd, recvOk, strlen(recvOk)) > 0)
                {
                    fprintf(stderr, "\t\t%s的[%d]消息已回复OK\n", currentClient->address, num);
                }
                bzero(buf, SIZE);
            }
            usleep(500000);
        }
    }

*/