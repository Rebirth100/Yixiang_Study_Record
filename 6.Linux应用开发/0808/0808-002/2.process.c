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
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("我是子进程%d ,我的id是:%d\n", pid, getpid());
    }
    if (pid > 0)
    {
        printf("我是父进程%d, 我的id是:%d\n", pid, getpid());
    }

    pause();
}

// #include <unistd.h>
// pid_t fork(void);