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
#include <time.h>
#define SIZE 128

void *readServerDatas(void*);

int main()
{
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
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
    socklen_t len = sizeof(serverAddress);

    if (connect(socketFd, (struct sockaddr *)&serverAddress, len))
    {
        perror("connect失败");
        return 0;
    }
    fprintf(stderr, "连接 成功\n");

    // 启动线程接受服务器数据
    pthread_t ptid;
    pthread_create(&ptid, NULL, readServerDatas,&socketFd );

    char buf[SIZE] = "\0";
    int index = 0;
    srand(time(0));
    while (1)
    {
        sprintf(buf, "%d#hello#%d", index, rand() % 900000 + 100000);
        if (write(socketFd, buf, strlen(buf)) > 0)
        {
            fprintf(stderr, "数据[%d]发送成功:%s\n", index, buf);
            index++;
            sleep(rand() % 5 + 1);
            bzero(buf, SIZE);
        }
    }
}

void *readServerDatas(void*args)
{
    fprintf(stderr, "接受数据线程(%ld)已启动\n",pthread_self());
    if(args==NULL)
    {
        return NULL ;
    }
    int *sockFd=(int*)args;
     char buf[SIZE] = "\0";
     char type[8]="\0";
     int num;
    int index = 0;
    while (1)
    {
        if (read(*sockFd, buf, SIZE) > 0)
        {
            fprintf(stderr, "\t\t\t收到服务器数据:%s\n",buf);
            //5#OK#
            num=-1;
            bzero(type,8);
            sscanf(buf,"%d#%s#",&num,type);
            fprintf(stderr,"\t\t\tnum:%d type:%s\n",num,type);
            if(strcmp(type,"OK")==0)
            {
                fprintf(stderr,"\t\t\t[%d]消息服务器已确认\n",num);
            }
        }
        usleep(500000);
    }
}