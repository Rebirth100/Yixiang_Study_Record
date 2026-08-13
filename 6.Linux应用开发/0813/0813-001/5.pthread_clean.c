#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

int threadCount = 2000;
int currentTime = 0;
pthread_mutex_t mtx;

pthread_t ptid[2];

void *add(void *);
void *displayTime(void *);
struct pthreadPos
{
    pthread_t *start;
    pthread_t *current;
};

//解锁函数
void  handerUnlock()
{
    pthread_mutex_unlock(&mtx);
    fprintf(stderr,"我帮助主动解锁啦啦啦啦");
}

int main()
{
    pthread_mutex_init(&mtx, NULL);
    pthread_t ptime;
    pthread_create(ptid, NULL, add, NULL);
    pthread_create(ptid + 1, NULL, add, NULL);

    if (pthread_create(&ptime, NULL, displayTime, NULL) != 0)
    {
        perror("pthread_create错误");
        exit(0);
    }
    pthread_join(ptid[0], NULL);
    pthread_join(ptid[1], NULL);

    fprintf(stderr, "MainExit\n");
     fprintf(stderr,"程序结束");
}
void *displayTime(void *args)
{
    int i=rand()%5+5;
    while (1)
    {
        if(i==currentTime)
        {
            pthread_cancel(ptid[rand()%2]);
        }
        fprintf(stderr, "time:%d\n", currentTime);
        sleep(1);
        currentTime++;
    }
}

void *add(void *args)
{
    fprintf(stderr, "线程[%ld]启动\n", pthread_self());
    //提前将解锁函数压栈，防止意外取消时自动帮助解锁
    pthread_cleanup_push(handerUnlock,NULL);
    for (int i = 0; i < threadCount; i++)
    {
        pthread_mutex_lock(&mtx);
        fprintf(stderr, "\t\t\t(%#lx#%d\n", pthread_self(), i);
        usleep(50000);
        pthread_mutex_unlock(&mtx);
    }
    //如果没有意外取消，则也清理函数栈
    pthread_cleanup_pop(0);
    pthread_exit(NULL);
}

//自旋锁


//生产者/消费者