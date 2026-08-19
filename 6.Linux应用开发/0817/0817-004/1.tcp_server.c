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
#include <sys/poll.h>

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

int main(int argc, char **argv)
{
    char port[8] = "9000";
    if (argc == 2)
    {
        sprintf(port, "%s", argv[1]);
    }
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

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(port));
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
    bzero(clientArray, sizeof(tcpClient *) * CLIENT_COUNT);

    // 准备poll信号集
    struct pollfd clientPollArray[CLIENT_COUNT];
    bzero(clientPollArray, sizeof(struct pollfd) * CLIENT_COUNT);
    clientPollArray[0].fd = serverFd;
    for (int i = 0; i < CLIENT_COUNT; i++)
    {
        clientPollArray[i].events = POLLIN | POLLERR;
    }
    int maxFd = serverFd;

    int currentClientCount = 0;

    struct sockaddr_in peerAddress;
    char addressInfo[32] = "\0";
    int newFd;
    tcpClientStatus newClientStatus;
    int tempClientCount = -1;

    // 检查是否有新的信号需要处理
    while (1)
    {
        if (poll(clientPollArray, maxFd + 1, -1) == 0)
        {
            continue;
        }
        // 检查是否有新的连接
        if (clientPollArray[0].revents & POLLIN)
        {
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
                maxFd++;

                //添加新 的客户端fd到信号集
                clientPollArray[currentClientCount].fd = newClient->fd;
 
                // 清理现有的客户端状态临时空间
                bzero(&newClientStatus, sizeof(newClientStatus));
                // 保存新的客户端状态信息
                strcpy(newClientStatus.address, addressInfo);
                newClientStatus.status = 1;
                // 清理共享内存
                bzero(clientStatus, sizeof(clientStatus));
                // 拷贝新的客户端状态到共享内存
                memcpy(clientStatus, &newClientStatus, sizeof(newClientStatus));
                fprintf(stderr, "已发送新的客户端%s上线信息到共享内存\n", clientStatus->address);
            }
        }

        for (int i = 1; i <=currentClientCount; i++)
        {
            char buf[SIZE] = "\0";
            char recvOk[SIZE] = "\0";
            tcpClient *currentClient = clientArray[i-1];
            if (clientPollArray[i].revents & POLLIN)
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
    }
}

/* *******************************
 #include <poll.h>
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
 struct pollfd {
               int   fd;
               short events;
               short revents;
           };

*********************/

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