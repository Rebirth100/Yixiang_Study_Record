#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <strings.h>
#include  <unistd.h>
#include  <signal.h>
void getSignal(int );
int main()
{
    for(int i=1;i<=64;i++)
    {
        if(i==31||i==32)
        {
            continue;
        }
        if(i%2==1)
        {
            //奇数信号被忽略
             signal(i,SIG_IGN);
             fprintf(stderr,"信号%d已设置忽略\n",i);
             continue;
        }
        //注册偶数信号处理函数
        signal(i,getSignal);
        fprintf(stderr,"注册信号%d处理函数\n",i);

    }
   
    pid_t  pid=getpid();
    int n=0;
    while(1)
    {
        fprintf(stderr,"我是[%d] 启动了:%d秒\n",pid,++n);
        sleep(1);
    }
     
}

void getSignal(int sig)
{
    fprintf(stderr,"收到信号:%d\n",sig);
    for(int i=0;i<100;i++)
    {
        fprintf(stderr,"#");
        usleep(10000);
    }
     fprintf(stderr,"\n\n");
}

// #include <signal.h>
// typedef void (*sighandler_t)(int);
// sighandler_t signal(int signum, sighandler_t handler);
