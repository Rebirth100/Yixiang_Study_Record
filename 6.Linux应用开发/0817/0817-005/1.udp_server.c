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
int main()
{
    int serverFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverFd == -1)
    {
        perror("socket失败");
        return 0;
    }
    fprintf(stderr, "socket成功  fd=%d\n", serverFd);
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
    fprintf(stderr, "bind成功 ,udp服务器运行于0.0.0.0:9000\n");

    struct sockaddr_in peerAddress;
    char buf[SIZE] = "\0";
    while (1)
    {
        bzero(buf,SIZE);
        bzero(peerAddress,sizeof(peerAddress));
        if (recvfrom(serverFd, buf, SIZE, 0, (struct sockaddr *)&peerAddress, &len) > 0)
        {
            fprintf(stderr, "%s:%d说:%s\n", inet_ntoa(peerAddress.sin_addr), ntohs(peerAddress.sin_port), buf);
        }
    }
}