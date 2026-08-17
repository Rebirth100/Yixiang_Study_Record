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

    fprintf(stderr, "服务器启动 监听 %s:%d \n", inet_ntoa(serverAddress.sin_addr),ntohs(serverAddress.sin_port));

    struct sockaddr_in peerAddress;

    while (1)
    {
        int newFd = accept(serverFd, (struct sockaddr *)&peerAddress, &len);
        if (newFd == -1)
        {
            continue;
        }
        fprintf(stderr, "有新的客户端链接 %s:%d\n", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port));
    }
}