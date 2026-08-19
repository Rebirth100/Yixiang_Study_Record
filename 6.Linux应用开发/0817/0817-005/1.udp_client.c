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
    int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd == -1)
    {
        perror("socket失败");
        return 0;
    }
    fprintf(stderr, "socket成功  fd=%d\n", socketFd);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9000);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.168.97");

    struct sockaddr_in backAddress;
    backAddress.sin_family = AF_INET;
    backAddress.sin_port = htons(9000);
    backAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t len = sizeof(serverAddress);

    char buf[SIZE] = "\0";
    int begin = 0, end = 1000;
    while (1)
    {
        sleep(rand() % 3 + 2);
        bzero(buf, SIZE);
        sprintf(buf, "%d#Hello#%d", begin++, rand() % 10000 + 10000);
        if (sendto(socketFd, buf, strlen(buf), 0, (struct sockaddr *)&serverAddress, len) > 0)
        {
            fprintf(stderr, "向%s:%d发送了%s\n", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port), buf);
        }

        usleep(500000);
        bzero(buf, SIZE);
        sprintf(buf, "%d#Hello#%d", end--, rand() % 10000 + 10000);
        if (sendto(socketFd, buf, SIZE, 0, (struct sockaddr *)&backAddress, len) > 0)
        {
            fprintf(stderr, "%s:%d说:%s\n", inet_ntoa(backAddress.sin_addr), ntohs(backAddress.sin_port), buf);
        }
    }
}