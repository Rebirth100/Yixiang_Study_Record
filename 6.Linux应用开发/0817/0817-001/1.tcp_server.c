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
#define CLIENT_SIZE
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

void *readClientDatas(void *args);

void cleanChild(int sig);

int main()
{
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        perror("socket失败");
        return 0;
    }
    fprintf(stderr, "socket成功  fd=%d\n", serverFd);

    //端口可复用 
    int rUseAddr=1;
    setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&rUseAddr,sizeof(rUseAddr))  ;


    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9000);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.168.97");
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

    fprintf(stderr, "服务器启动 监听 %s:%d \n", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));

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

    signal(SIGCHLD,cleanChild);

    struct sockaddr_in peerAddress;
    char addressInfo[32] = "\0";
    int newFd;
    tcpClientStatus newClientStatus;
    tcpClient currentClient;
    while (1)
    {
        newFd = accept(serverFd, (struct sockaddr *)&peerAddress, &len);
        if (newFd == -1)
        {
            continue;
        }
        fprintf(stderr, "有新的客户端链接 %s:%d\n", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));

        // 启动新进程服务当前客户端
        pid_t clientPid = fork();

        // 父进程向共享内存保存新的连接信息
        if (clientPid > 0)
        {
            bzero(addressInfo, sizeof(addressInfo));
            sprintf(addressInfo, "%s:%d", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));

            // 清理现有的客户端状态临时空间
            bzero(&newClientStatus, sizeof(newClientStatus));
            // 保存新的客户端状态信息
            strcpy(newClientStatus.address, addressInfo);
            newClientStatus.status = 1;

            bzero(clientStatus,sizeof(clientStatus));
            
            // 拷贝新的客户端状态到共享内存
            memcpy(clientStatus, &newClientStatus, sizeof(newClientStatus));
            fprintf(stderr, "已发送新的客户端%s上线信息到共享内存\n", clientStatus->address);
            // 关闭新的客户端socket
            close(newFd);
        }

        if (clientPid == 0)
        {
            currentClient.fd = newFd;
            sprintf(currentClient.address, "%s:%d", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
            break;
        }
    }

    // 子进程继续服务(读写数据)
    close(serverFd);
    char buf[SIZE] = "\0";
    char recvOk[SIZE] = "\0";
    int index = 0;
    while (1)
    {
        if (read(newFd, buf, SIZE) > 0)
        {
            fprintf(stderr, "%s说:%s\n", currentClient.address, buf);
            // 0#hello#789383
            int num, value;
            sscanf(buf, "%d#hello#%d", &num, &value);
            fprintf(stderr, "\t\t收到%s的[%d]消息\n", currentClient.address, num);
            bzero(recvOk, SIZE);
            sprintf(recvOk, "%d#OK #", num);
            if (write(newFd, recvOk, strlen(recvOk)) > 0)
            {
                fprintf(stderr, "\t\t%s的[%d]消息已回复OK\n", currentClient.address, num);
            }
            bzero(buf, SIZE);
        }
        usleep(500000);
    }
}



//收到子进程退出信号时，清理子进程现场后退出
void cleanChild(int sig)
{
    if(sig==SIGCHLD)
    {
        while (waitpid(-1,NULL,WNOHANG)>0);       
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
