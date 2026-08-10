#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>

int main()
{
    int mainPid=getpid();
    for(int i=0;i<6;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
           break;
        }
        if(pid>0)
        {
            printf("pid=%d\n",pid);
        }
    }

    if(mainPid!=getpid())
    {
        printf("我是子进程 我的id=%d\n",getpid());
    }

    pause();

}

//作业:父进程上报自己生产的子进程ID，子进程自己上报自己的ID，
//要求父进程上报信息连续，子进程上报信息连续