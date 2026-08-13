#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>
void *routine(void *);
int main()
{
    pthread_t ptid;
    pthread_attr_t attr;
    int endValue = rand() % 50 + 50;
    pthread_attr_init(&attr);
    int detacgStatus = -1;
    //配置线程属性为可接合
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_attr_getdetachstate(&attr, &detacgStatus);
    fprintf(stderr, "##detacgStatus=%d##\n", detacgStatus);
    getchar();
    if (pthread_create(&ptid, &attr, routine, (void *)&endValue) != 0)
    {
        perror("pthread_create错误");
        exit(0);
    }

    int calcelTime= rand()%25+25;
    for (int i = 0; i < 50; i++)
    {
        fprintf(stderr, "##Main##\n");
        if(i==calcelTime)
        {
            //取消线程
           // pthread_cancel(ptid);
            usleep(100000);
        }
        usleep(50000);
    }

    int *endStatus = NULL;
    if (pthread_join(ptid, (void **)&endStatus) == 0)
    {
        fprintf(stderr, "接合成功 endStatus:%d\n", *endStatus);
    }
    else
    {
        fprintf(stderr, "接合失败\n");
    }
    fprintf(stderr, "Main结束\n");
    pthread_exit(NULL);
}

void *routine(void *args)
{
    //从线程内部主动分离(不可接合)
   // pthread_detach(pthread_self());
    int *end = NULL;
    if (args)
    {
        end = (int *)args;
    }
    static int endValue = 0;
    int cancel=rand()%50;
    if (end)
    {
        for (int i = 0; i < *end; i++)
        {
            if(i==cancel)
            {
                pthread_cancel(pthread_self());
            }
            fprintf(stderr, "\t\t(%#lX)->%d\n", pthread_self(), i);
            usleep(50000);
            endValue++;
        }
    }

    pthread_exit((void *)&endValue);
}

// #include <pthread.h>

// int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
// int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
//               detachstate:     PTHREAD_CREATE_DETACHED /PTHREAD_CREATE_JOINABLE