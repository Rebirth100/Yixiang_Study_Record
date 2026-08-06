#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include  <unistd.h>
// chmod  1764  a.txt   //rwxrw-r-T

int main()
{
    int fd = open("./a.txt", O_CREAT, 01764);
    if (fd == -1)
    {
        perror("创建文件失败");
        fprintf(stderr, "errNO:%d\n", errno);
        return errno;
    }
    fprintf(stderr, "创建文件成功 fd=%d\n", fd);
    close(fd);

    fd = open("./a1.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("打开文件失败");
        fprintf(stderr, "errNO:%d\n", errno);
        return errno;
    }
    fprintf(stderr, "只读打开文件成功 fd=%d\n", fd);
    close(fd);
    return 0;
}

// #include <fcntl.h>
// int open(const char *pathname, int flags, .../* mode_t mode */);

// #include <unistd.h>
// int close(int fd);
