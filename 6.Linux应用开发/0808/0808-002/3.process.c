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

int main()
{
    for(int i=0;i<6;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
            pause();
        }
        if(pid>0)
        {
            printf("pid=%d\n",pid);
        }
    }

    pause();

}