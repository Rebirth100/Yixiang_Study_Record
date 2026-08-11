#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
int main()
{
    key_t key = ftok(".", 109);
    if (key == -1)
    {
        perror("ftok失败");
        return 0;
    }
    fprintf(stderr, "ftok完毕 key:%#x\n", key);

    int shmID = shmget(key, SHM_SIZE, IPC_CREAT | 0664);
    if (shmID == -1)
    {
        perror("shmget失败");
        return 0;
    }
    fprintf(stderr,"获得共享内存%d\n",shmID);
    char *message=shmat(shmID,NULL,0);
    if(message==NULL)
    {
         return 0;
    }
    fprintf(stderr,"共享映射完毕 message:%p\n",message);

    
    while (1)
    {
        if (strlen(message) > 0)
        {
            fprintf(stderr, "进程[%d]读取消息%s\n", getpid(), message);
            bzero(message,SHM_SIZE);
        }
        sleep(1);
    }
    
    return 0;
}


//1.录屏作业 ：讲解进程间通信  信号通信方式
//2.代码作业；
//  两进程通过共享内存进行通信，发送方的第一条消息是本次通信共发送的数据个数
//  按约定的个数发送Hello消息后，自己退出
//  接受方显示所有收到的消息后，删除共享内存资料后，自己也退出

// #include <sys/ipc.h>
// key_t ftok(const char *pathname, int proj_id);

// #include <sys/shm.h>
// int shmget(key_t key, size_t size, int shmflg);

//  #include <sys/shm.h>
// //映射共享内存到当前进程
// void *shmat(int shmid, const void *_Nullable shmaddr, int shmflg);
// //让共享内存从当前进程分离
// int shmdt(const void *shmaddr);

//删除/状态控制/调整
// #include <sys/shm.h>
//int shmctl(int shmid, int op, struct shmid_ds *buf);
