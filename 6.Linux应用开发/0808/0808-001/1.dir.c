#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
int main(int argc, char **argv)
{
        if (argc != 2)
        {
                fprintf(stderr, "命令错误: %s 路径\n", argv[0]);
                return 0;
        }
        struct stat sb;
        if (lstat(argv[1], &sb))
        {
                perror("lstat错误");
                return 0;
        }

        if (!S_ISDIR(sb.st_mode))
        {
                fprintf(stderr, "%s不是1个目录\n", argv[1]);
                return 0;
        }

        DIR *Dir = opendir(argv[1]);
        if (Dir)
        {
             struct dirent  *dir=  readdir(Dir);
             while(dir)
             {
                fprintf(stderr,"inode:%ld type:%c name:%s\n",
                dir->d_ino,
                dir->d_type,
                dir->d_name
                );
                dir=  readdir(Dir);
             }
        }
}

/*******************opendir************************ */
// #include <sys/types.h>
// #include <dirent.h>

// DIR *opendir(const char *name);
// DIR *fdopendir(int fd);

/*******************判断是否是目录************************ */
//  if ((sb.st_mode & S_IFMT) == S_IFDIR)
//  {

//  }

// S_ISREG(m)  is it a regular file?
// S_ISDIR(m)  directory?
// S_ISCHR(m)  character device?
// S_ISBLK(m)  block device?
// S_ISFIFO(m) FIFO (named pipe)?
// S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
// S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

/*******************读目录************************ */
// #include <dirent.h>
// struct dirent *readdir(DIR *dirp);
// struct dirent
// {
//         ino_t d_ino;             /* Inode number */
//         off_t d_off;             /* Not an offset; see below */
//         unsigned short d_reclen; /* Length of this record */
//         unsigned char d_type;    /* Type of file; not supported
//                                     by all filesystem types */
//         char d_name[256];        /* Null-terminated filename */
// };
