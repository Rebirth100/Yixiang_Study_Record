#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "命令错误 %s 文件路径\n", argv[0]);
        return 0;
    }
    struct stat sb;
    if (lstat(argv[1], &sb))
    {
        perror("调用lstat错误");
        return 0;
    }

    mode_t fileMode = sb.st_mode;
    // printf("fileMode:%d  %o %x\n",fileMode,fileMode,fileMode);
    // printf("fileMode:%d  %#o %#x\n",fileMode,fileMode,fileMode);
    printf("%-20s\tmode:%#o\n", argv[1], fileMode);

    char type = '\0';
    switch (fileMode & 0770000)
    {
    case 0100000:
        type = '-';
        break;
    case 040000:
        type = 'd';
        break;
    case 010000:
        type = 'p';
        break;
    case 0120000:
        type = 'l';
        break;
    case 060000:
        type = 'b';
        break;
    case 020000:
        type = 'c';
        break;
    case 0140000:
        type = 's';
        break;
    default:
        type = '?';
        break;
    }
    printf("%-20s\ttype:%c\n", argv[1], type);
}

// S_IFMT     0170000   bit mask for the file type bit field
// S_IFSOCK   0140000   socket
// S_IFLNK    0120000   symbolic link
// S_IFREG    0100000   regular file
// S_IFBLK    0060000   block device
// S_IFDIR    0040000   directory
// S_IFCHR    0020000   character device
// S_IFIFO    0010000   FIFO

// a     010 0664  =>010 0664 & 077 0000
//  77 => 001 111  =>2^4 => 0~15 =>16

// ./app   a
// a                       010 0664  =>18Bit
// ./app   /home
// /home                    04          0755
// ./app   /home/hgg/ptest
// /home/hgg/ptest         01           0664
// ./app   /home/hgg/i.c
// /home/hgg/i.c           012          0777
// ./app   /dev/sda2
// /dev/sda2               06           0660
// ./app   /dev/tty0
// /dev/tty0               02           0620
// ./app   /run/user/1000/bus
// /run/user/1000/bus      014          0666

//  l  p  c  b  s  - d

//
// struct  Date
// {
//     int year:14
//     int month:4
//     int day:5
// };

// 0664=>000 110 110  100 =>rw- rw- r--