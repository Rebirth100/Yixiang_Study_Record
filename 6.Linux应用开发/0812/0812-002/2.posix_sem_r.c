#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#define SEM_SHM_SIZE 2

// 准备数据源
void setSourText(char *sourText);

int main()
{

    sem_t *data = sem_open("/datas", O_CREAT, 0664, 1);
    if (data == NULL)
    {
        perror("sem_open错误");
        return 0;
    }
    sem_t *space = sem_open("/spaces", O_CREAT, 0664, 1);
    if (sem_open == NULL)
    {
        perror("sem_open错误");
        return 0;
    }

        // 初始化信号量
    sem_init(data, 1, 0);
    sem_init(space, 1, 1);

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

    size_t index = 0;
    bzero(data, SEM_SHM_SIZE);
    int value;
    while (1)
    {
        sleep(1);
        // P操作
        sem_getvalue(data, &value);
        fprintf(stderr, "\t\tdata:%d\n", value);
        sem_getvalue(space, &value);
        fprintf(stderr, "\t\tspace:%d\n", value);
        puts("\t\t申请Data");
        sem_wait(data);

        // 读数据
        fprintf(stderr, "有数据%s\n", add);
        sleep(1);

        // V操作
        sem_post(space);
         sem_getvalue(data, &value);
        fprintf(stderr, "\t\tdata:%d\n", value);
        sem_getvalue(space, &value);
        fprintf(stderr, "\t\tspace:%d\n", value);
        puts("\t\t释放space");
        sleep(1);
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
