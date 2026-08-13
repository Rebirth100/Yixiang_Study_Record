#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

int globalCount = 0;
 
int threadCount =   10000000;

pthread_mutex_t mtx;

void* add(void *);

struct pthreadPos
{
    pthread_t *start;
    pthread_t *current;
};

int main()
{
    pthread_mutex_init(&mtx,NULL);
    pthread_t ptid[10];
    struct pthreadPos pos[10];
    for (int i = 0; i < 10; i++)
    {
        pos[i].start = ptid;
        pos[i].current = ptid + i;
        if (pthread_create(ptid+i, NULL, add,(void*)( pos+i)) != 0)
        {
            perror("pthread_create错误");
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(ptid[i],NULL);
    }
    fprintf(stderr,"MainExit:%d\n",globalCount);

}

void *add(void *args)
{
    int n=0;
    if(args!=NULL)
    {
        struct pthreadPos *pos=(struct pthreadPos *)args;
        n=pos->current-pos->start;
    }
    
    fprintf(stderr, "线程[%d]启动\n",n );
    for (int i = 0; i < threadCount; i++)
    {
        pthread_mutex_lock(&mtx);
        globalCount++;
        pthread_mutex_unlock(&mtx);
    }
    pthread_exit(NULL);
}