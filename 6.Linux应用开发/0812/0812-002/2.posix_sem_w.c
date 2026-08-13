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
#define SEM_SHM_SIZE 2

// 准备数据源
void setSourText(char *sourText);

int main()
{
    sem_t *data = sem_open("/datas", O_CREAT, 0664, 1);
    sem_t *space = sem_open("/spaces", O_CREAT, 0664, 1);
    if (data == NULL || space == NULL)
    {
        perror("sem_open错误");
        return 0;
    }



    key_t shmKey = ftok(".", 1089);
    if (shmKey == -1)
    {
        perror("shm_ftok错误");
        return 0;
    }
    int shmId = shmget(shmKey, SEM_SHM_SIZE, IPC_CREAT | 0666);
    if (shmId == -1)
    {
        perror("shmget错误");
        return 0;
    }
    fprintf(stderr, "共享内存 id:[%#x] key:[%#x]已就绪\n", shmId, shmKey);

    char *add = shmat(shmId, NULL, SEM_SHM_SIZE);
    if (add == NULL)
    {
        perror("shmat错误");
        return 0;
    }
    fprintf(stderr, "共享内存映射完毕 data=%p\n", add);
    char sourText[64];
    // 初始化数据源
    setSourText(sourText);

    size_t index = 0;
    bzero(add, SEM_SHM_SIZE);
    int value;
    while (1)
    {
        sleep(1);
        // P操作
         sem_getvalue(data, &value);
        fprintf(stderr, "\t\tdata:%d\n", value);
        sem_getvalue(space, &value);
        fprintf(stderr, "\t\tspace:%d\n", value);
        puts("\t\t申请space");
        sem_wait(space);

        // 写数据
        add[0] = sourText[(index++) % 64];
        fprintf(stderr, "写入数据%c\n", *add);
        sleep(1);

        // V操作
        sem_post(data);
        sem_getvalue(data, &value);
        fprintf(stderr, "\t\tdata:%d\n", value);
        sem_getvalue(space, &value);
        fprintf(stderr, "\t\tspace:%d\n", value);
        puts("\t\t释放了data");
    }
}

void setSourText(char *sourText)
{
    bzero(sourText, 64);
    for (int i = 0; i < 26; i++)
    {
        sourText[i] = 'A' + i;
    }
    for (int i = 0; i < 26; i++)
    {
        sourText[i + 26] = 'a' + i;
    }
    for (int i = 0; i < 10; i++)
    {
        sourText[i + 52] = '0' + i;
    }
}


//posix信号量多进程之间要保证全局只初始化1次
//先启动read，用read初始化；再启动write

//sem_init 初始化信号量
//sem_wait  p操作，申请资源
//sem_post  v操作，释放资源
//sem_getvalue 查看信号量的状态值
