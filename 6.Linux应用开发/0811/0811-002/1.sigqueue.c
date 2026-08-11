#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
int main()
{
    pid_t pid;
    int sigNum;
    union sigval sendValue;
    int data=0;
    while(1)
    {
        printf("请输入目标进程:");
        scanf("%d",&pid);
        printf("请输入要发送给进程(%d)的数据(50以内)\n",pid);
        scanf("%d",&(data));
        for(int i=1;i<8;i++)
        {
            sendValue.sival_int=data*i;
            if(sigqueue(pid,i,sendValue)==-1)
            {
                perror("发送信号错误");
            } 
            sleep(3);
        }
    }
}

/********************************** */
// #include <signal.h>
// int sigqueue(pid_t pid, int sig, const union sigval value);
// union sigval
// {
//     int sival_int;
//     void *sival_ptr;
// };
