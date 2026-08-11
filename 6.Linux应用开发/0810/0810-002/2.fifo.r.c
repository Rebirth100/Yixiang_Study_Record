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
#include <fcntl.h>
#define SIZE 128
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "命令错误:%s 管道文件名\n", argv[0]);
        return 0;
    }
    if (access(argv[1], F_OK))
    {
        fprintf(stderr, "管道检查失败，我来创建\n");
        if (mkfifo(argv[1], 0777) == -1)
        {
            perror("创建管道失败");
            return 0;
        }
        fprintf(stderr, "管道创建完毕\n");
    }
    fprintf(stderr, "管道检查成功\n");

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "打开管道失败\n");
        return 0;
    }
    fprintf(stderr, "打开管道成功\n");
    char recvText[SIZE] = "\0";
    while (1)
    {
        if (read(fd, recvText, 128) > 0)
        {
            fprintf(stderr, "进程[%d]读取消息%s\n", getpid(), recvText);
        }
        sleep(1);
    }
}