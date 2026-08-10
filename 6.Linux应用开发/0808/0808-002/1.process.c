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

int  main()
{
    for(int i=0;i<6;i++)
    {
        fork();
        printf("我是进程[%d] 我的父进程是:[%d]\n",getpid(),getppid());
    }
   

    pause();
}



// #include <unistd.h>
// pid_t fork(void);