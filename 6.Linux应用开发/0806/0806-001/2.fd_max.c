#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <strings.h>
#include  <fcntl.h>
#include  <errno.h>
#include  <unistd.h>
//获取当前进程可打开的文件的文件描述符的所有值
int main(int  argc,char **argv)
{
    if(argc!=2)
    {
        printf("命令错误:%s 已存在的文件名\n",argv[0]);
        return 1;
    }
 
    printf("max=%ld\n",sysconf(_SC_OPEN_MAX));
    getchar();
    int fd=-1;
    int count=0;
    while(1)
    {
        fd=open(argv[1],O_RDONLY);
        if(fd==-1)
        {
            perror("");
            printf("count=%d\n",count);
            break;
        }
        printf("fd=%d\n",fd);
        count++;
    }

 
   printf("max=%ld\n",sysconf(_SC_OPEN_MAX));
    return 0;

}

