#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
 #include <semaphore.h>
 #include <signal.h>
#include <stdlib.h>
#include <errno.h>
 
void *routine(void *args)
{
 
    printf("%s",__FUNCTION__);
 
    char *data=(char *)args;
    int i=0;
    if(*data=='A')
    {
        nice(0);
    }
    if(*data=='B')
    {
        nice(0);
    }
    while(1)
    {
        usleep(20000);
        i=(i+1)%1024;
        fprintf(stderr,"%d->%c\t",i,data[i]);
        if(i+1==1023)
        {
            getchar();
        }
    }
}

int main()
{
    char str1[1024]="";
    char str2[1024]="";
    int i;
    for(i=0;i<1024;i++)
    {
        str1[i]='A';
        str2[i]='B';
    }

    pthread_t tid1,tid2;
    pthread_attr_t attr1,attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //设置调度
    //PTHREAD_INHERIT_SCHED    采用默认
    //PTHREAD_EXPLICIT_SCHED  采用属性中设置的
    // pthread_attr_setinheritsched(&attr1,PTHREAD_INHERIT_SCHED);
    // pthread_attr_setinheritsched(&attr2,PTHREAD_INHERIT_SCHED);

    // pthread_create(&tid2,&attr2,routine,str2);
    // pthread_create(&tid1,&attr1,routine,str1);
    printf("%s",__FUNCTION__);

    pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
    //  pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);//先进先出
    pthread_attr_setschedpolicy(&attr1,SCHED_RR);//轮巡
    // pthread_attr_setschedpolicy(&attr1,SCHED_OTHER);//动态调整
   //   pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr2,SCHED_RR);
    struct sched_param param1;
    param1.sched_priority=10;
    struct sched_param param2;
     param2.sched_priority=90;

    pthread_attr_setschedparam(&attr1,&param1);
    pthread_attr_setschedparam(&attr2,&param2);
    pthread_create(&tid2,&attr1,routine,str2);
    pthread_create(&tid1,&attr2,routine,str1);
    
    // pthread_create(&tid2,NULL,routine,str2);
    // pthread_create(&tid1,NULL,routine,str1);


    pause();
    return 0;
}