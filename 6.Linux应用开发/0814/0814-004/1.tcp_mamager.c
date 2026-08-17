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
#define CLIENT_SIZE 1024
#define SIZE 128
// 客户端状态
typedef struct
{
    char address[32];
    int status;
} tcpClientStatus;

int main()
{
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
    tcpClientStatus clientStatusArray[CLIENT_SIZE];
    int currentClientSize = 0;
    bzero(clientStatusArray, sizeof(tcpClientStatus) * CLIENT_SIZE);

    while (1)
    {
        if (strlen((char *)clientStatus) > 0)
        {
            fprintf(stderr, "有新的客户端信息");
            if (clientStatus->status == 1)
            {
                fprintf(stderr, "%s 上线\n",clientStatus->address);
                //将新的客户端信息和现有的列表比对，如果没有当前的信息，则添加到末尾
                int  exists=0;
                for (int i = 0; i < currentClientSize; i++)
                {
                   if(strcmp(clientStatus->address,clientStatus[i].address)==0)
                   {
                    exists++;
                    break;
                   }
                }
                if(exists==0)
                {
                    memcpy(clientStatusArray + currentClientSize, clientStatus, sizeof(tcpClientStatus));
                    currentClientSize++;
                }
                //建议启动新的线程每30秒刷新显示列表
                system("clear");
                fprintf(stderr, "+++++++ 在线客户端列表 +++++++ \n");
                for (int i = 0; i < currentClientSize; i++)
                {
                    fprintf(stderr, "[%-4d]\t->%s\n", i, clientStatusArray[i].address);
                }
            }
            else
            {
                fprintf(stderr, "%s 下线\n",clientStatus->address);
            }
            //bzero(clientStatus,sizeof(clientStatus));
        }
    }
}