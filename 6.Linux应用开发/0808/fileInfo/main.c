#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "file_info.h"
int main(int argc, char **argv)
{
        int hasDPos = 0, hasDCount = 0;
        char infoText[256];
        if (argc == 1)
        {
                bzero(infoText, 256);
                dirFileInfo(".", infoText);
                return 0;
        }

        for (int i = 1; i < argc; i++)
        {
                if (strcmp("-d", argv[i]) == 0)
                {
                        hasDPos = i;
                        hasDCount++;
                }
        }
#ifdef DEBUG
        fprintf(stderr, "有-d  pos:%d\n", hasDPos);
#endif
        if (argc == 2)
        {
                //./app -d
                if (hasDPos)
                {
#ifdef DEBUG
                        fprintf(stderr, "执行 ./app -d\n");
#endif
                        bzero(infoText, 256);
                        fileInfo(".", infoText);
                        fprintf(stderr, "%s %s\n", infoText, ".");
                        return 0;
                }
                //./app /home
                //./app /home/hgg/ptest
                if (isDirect(argv[1]))
                {
                        bzero(infoText, 256);
                        dirFileInfo(argv[1], infoText);
                        return 0;
                }
                fileInfo(argv[1], infoText);
                fprintf(stderr, "%s %s\n", infoText, argv[1]);
                return 0;
        }
        // 3个及以上多参数
        if (hasDCount == argc - 1)
        {
                bzero(infoText, 256);
                fileInfo(".", infoText);
                fprintf(stderr, "%s %s\n", infoText, ".");
                return 0;
        }

        if (hasDPos)
        {
                for (int i = 1; i < argc; i++)
                {
                        if (strcmp("-d", argv[i]) == 0)
                        {
                                continue;
                        }
                        bzero(infoText, 256);
                        fileInfo(argv[i], infoText);
                        fprintf(stderr, "%s %s\n", infoText, argv[i]);
                }
                return 0;
        }

        for (int i = 1; i < argc; i++)
        {
                if (isDirect(argv[i]))
                {
                        bzero(infoText, 256);
                        fprintf(stderr,"%s\n",argv[i]);
                        dirFileInfo(argv[i], infoText);
                        fprintf(stderr,"\n");
                        continue;
                }

                bzero(infoText, 256);
                fileInfo(argv[i], infoText);
                fprintf(stderr, "%s %s\n", infoText, argv[i]);
        }


        return 0;
}