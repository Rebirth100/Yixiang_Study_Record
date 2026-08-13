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
#define SEM_SHM_SIZE 2
void *routine(void *);
int main()
{
    srand(time(0));
    pthread_t ptid;
    pthread_create(&ptid,NULL,routine,NULL);

    for(int i=0;i<100;i++)
    {
         fprintf(stderr,"main线程%ld,i=%d\n",pthread_self(),i);
         usleep(100000);
    }

    //main函数返回，则进程结束
    //return 0;

    int *end=NULL;
    if(pthread_join(ptid,(void **)&end)==0)
    {
        fprintf(stderr,"退出状态是:%d\n",*end);
    }
    else
    {
        fprintf(stderr,"线程接合失败\n");
    }
    fprintf(stderr,"M-M main线程结束 M-M\n");
    pthread_exit(NULL);
}

void *routine(void *args)
{
    fprintf(stderr,"\t\t\t子线程启动:%ld\n",pthread_self());
    static int  end=0;
    end=rand()%100+100;
    for(int i=0;i<end;i++)
    {
         fprintf(stderr,"\t\t\t子线程%ld,i=%d\n",pthread_self(),i);
         usleep(100000);
    }
    //pthread_exit(&end);
    exit(0);
}


//启动一个新的线程
// #include <pthread.h>

// int pthread_create(pthread_t *restrict thread,
//                    const pthread_attr_t *restrict attr,
//                    void *(*start_routine)(void *),
//                    void *restrict arg);


//线程结束
//#include <pthread.h>
//void pthread_exit(void *retval);


//线程内直接获得线程的ID
// #include <pthread.h>
// pthread_t pthread_self(void);


//线程接合  等待子线程退出   join
// #include <pthread.h>
// int pthread_join(pthread_t thread, void **retval);