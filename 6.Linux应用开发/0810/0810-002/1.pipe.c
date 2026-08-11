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
#include <signal.h>
#include <syslog.h>
#include <pwd.h>
#include <string.h>
#define SIZE 128
int main()
{
    int pipefd[2] = {-1, -1};
    int res = pipe(pipefd);
    if (res)
    {
        perror("创建管道失败");
        return 0;
    }
    fprintf(stderr, "匿名管道启动 [%d] <-> [%d]\n", pipefd[0], pipefd[1]);

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("创建进程失败");
        return 0;
    }
    if (pid > 0)
    {
        fprintf(stderr, "我是父进程，负责写数据\n");
        char datas[128];
        while (1)
        {
            bzero(datas, 128);
            sprintf(datas, "Hello#%d\n", rand() % 1000 + 1000);
            if (write(pipefd[1], datas, strlen(datas)) > 0)
            {
                fprintf(stderr, "父进程[%d]写入消息%s\n", getpid(),datas );
                sleep(rand()%3+3);
            }
        }
    }

    if (pid == 0)
    {
        fprintf(stderr, "我是子进程，负责读数据\n");
        char recvText[SIZE]="\0";
        while (1)
        {
            if(read(pipefd[0],recvText,128)>0)
            {
                fprintf(stderr, "子进程[%d]读取消息%s\n", getpid(),recvText );
            }
            sleep(1);
        }
    }
    return 0;
}

/********************************pipe*********************************** */
// #include <unistd.h>

// int pipe(int pipefd[2]);
// #define _GNU_SOURCE /* See feature_test_macros(7) */
// #include <fcntl.h>  /* Definition of O_* constants */
// #include <unistd.h>
// int pipe2(int pipefd[2], int flags);
// #include <unistd.h>
// struct fd_pair
// {
//     long fd[2];
// };