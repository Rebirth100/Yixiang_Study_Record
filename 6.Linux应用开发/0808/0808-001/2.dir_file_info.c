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
#include "file_info.h"
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

  char fileAttrib[256] = "\0";
  DIR *Dir = opendir(argv[1]);
  if (Dir)
  {
    struct dirent *dir = readdir(Dir);
    while (dir)
    {
      // fprintf(stderr, "inode:%ld name:%s\n",
      //         dir->d_ino,
      //         dir->d_name);
      // 获取并输出子文件属性
      // bzero(fileAttrib, 256);
      // char tempName[512] = "\0";
      // if (argv[1][strlen(argv[1]) - 1] == '/')
      // {
      //   sprintf(tempName, "%s%s", argv[1], dir->d_name);
      // }
      // else
      // {
      //   sprintf(tempName, "%s/%s", argv[1], dir->d_name);
      // }
      // if (fileInfo(tempName, fileAttrib))
      // {
      //   fprintf(stderr, "%s %s\n", fileAttrib, dir->d_name);
      // }
      // fprintf(stderr, "\n\n");

      chdir(argv[1]);
      if (fileInfo(dir->d_name, fileAttrib))
      {
        fprintf(stderr, "%s %s\n", fileAttrib, dir->d_name);
      }
      // fprintf(stderr, "\n\n");
      dir = readdir(Dir);
    }
  }
}

// #include <strings.h>
// void bzero(void s[.n], size_t n);

// #include <unistd.h>
// int chdir(const char *path);
// int fchdir(int fd);