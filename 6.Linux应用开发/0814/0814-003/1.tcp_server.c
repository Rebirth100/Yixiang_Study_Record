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
#define SIZE 128
typedef struct
{
    char address[32];
    int fd;
    char user[32];
} tcpClient;

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

void *readClientDatas(void *args);

int main()
{
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        perror("socket失败");
        return 0;
    }
    fprintf(stderr, "socket成功  fd=%d\n", serverFd);
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

    //准备共享内存，向内存中更新上线信息
    

    struct sockaddr_in peerAddress;
    char addressInfo[32] = "\0";
    int newFd;
    while (1)
    {
        newFd = accept(serverFd, (struct sockaddr *)&peerAddress, &len);
        if (newFd == -1)
        {
            continue;
        }
        fprintf(stderr, "有新的客户端链接 %s:%d\n", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
        bzero(addressInfo, sizeof(addressInfo));
        sprintf(addressInfo, "%s:%d", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
        tcpClient *newClient = initTcpClient(addressInfo, newFd);
        // 启动新线程服务当前客户端
        if (newClient)
        {
            pthread_t clientId;
            pthread_create(&clientId, NULL, readClientDatas, (void *)newClient);
        }
    }
}

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
            fprintf(stderr,"\t\t收到%s的[%d]消息\n",currentClient->address,num);
            bzero(recvOk,SIZE);
            sprintf(recvOk,"%d#OK #",num);
            if(write(currentClient->fd,recvOk,strlen(recvOk))>0)
            {
                fprintf(stderr,"\t\t%s的[%d]消息已回复OK\n",currentClient->address,num);
            }
            bzero(buf, SIZE);
        }
        usleep(500000);
    }
}