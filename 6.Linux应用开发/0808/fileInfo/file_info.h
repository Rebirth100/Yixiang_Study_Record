#ifndef FILE_INFO_260807_HGG_V0001
#define FILE_INFO_260807_HGG_V0001

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>
 
// TODO:文件信息fileInfo
char *fileInfo(const char *fileName, char *info);

// TODO:目录下的子文件信息
void dirFileInfo(const char *path, char *info);

// TODO:是否是目录
int isDirect(const char *path);

#endif