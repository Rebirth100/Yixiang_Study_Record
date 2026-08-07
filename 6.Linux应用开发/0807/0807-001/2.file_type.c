#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"命令错误 %s 文件路径\n",argv[0]);
        return 0;
    }
    struct stat   sb;
    if(lstat(argv[1],&sb))
    {
        perror("调用lstat错误");
        return 0;
    }
    char fileType='\0';
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device\n");
        fileType='b';
        break;
    case S_IFCHR:
        printf("character device\n");
        fileType='c';
        break;
    case S_IFDIR:
        printf("directory\n");
        fileType='d';
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        fileType='p';
        break;
    case S_IFLNK:
        printf("symlink\n");
        fileType='l';
        break;
    case S_IFREG:
        printf("regular file\n");
        fileType='-';
        break;
    case S_IFSOCK:
        printf("socket\n");
        fileType='s';
        break;
    default:
        printf("unknown?\n");
        fileType='?';
        break;
    }
    fprintf(stderr,"%s 的类型是:%c\n",argv[1],fileType);

    return  0;
}