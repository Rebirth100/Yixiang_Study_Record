#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "file_info.h"
#define TEST_COUNT 7
int main()
{
        char *filePath[TEST_COUNT] = {
            "a", "/home", "/home/hgg/ptest",
            "/dev/sda2", "/home/hgg/i.c",
            "/dev/tty0", "/run/user/1000/bus"};
        char fileAttrib[256] = "\0";
        for (int i = 0; i < TEST_COUNT; i++)
        {
                fprintf(stdout, "正在测试文件:%s\n", filePath[i]);
                if (fileInfo(filePath[i], fileAttrib))
                {
                        fprintf(stdout, "%s %s\n", fileAttrib, filePath[i]);
                }

                fprintf(stdout, "测试文件%s完毕\n\n\n\n", filePath[i]);
        }

        return 0;
}