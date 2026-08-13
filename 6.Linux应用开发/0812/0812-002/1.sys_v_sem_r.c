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
#include <sys/sem.h> //sys-v信号量
#define SEM_SHM_SIZE 2
#define DATA 0
#define SPACE 1

// 准备数据源
void setSourText(char *sourText);

union semun
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                              (Linux-specific) */
};

void sem_init(int semId, int index, int value);
void sem_p(int semId, int index);
void sem_v(int semId, int index);

int main()
{
    key_t semKey = ftok(".", 1088);
    if (semKey == -1)
    {
        perror("sem_ftok错误");
        return 0;
    }
    int semId = semget(semKey, SEM_SHM_SIZE, IPC_CREAT | 0666);
    if (semId == -1)
    {
        perror("semget错误");
        return 0;
    }
    fprintf(stderr, "信号量id:[%#x] key:[%#x]已就绪\n", semId, semKey);

    // 初始化信号量
    sem_init(semId, DATA, DATA);
    sem_init(semId, SPACE, SPACE);

    {
        // union semun semData;
        // semData.val=DATA;
        // semctl(semId,DATA,SETVAL,semData);
        // union semun semSpace;
        // semSpace.val=SPACE;
        // semctl(semId,SPACE,SETVAL,semSpace);
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

    char *data = shmat(shmId, NULL, SEM_SHM_SIZE);
    if (data == NULL)
    {
        perror("shmat错误");
        return 0;
    }
    fprintf(stderr, "共享内存映射完毕 data=%p\n", data);

    size_t index = 0;

    while (1)
    {
        sleep(1);
        // P操作
        sem_p(semId, DATA);
        sleep(1);
        // 读数据
        fprintf(stderr, "有数据%s\n", data);
        // v操作
        sem_v(semId, SPACE);
    }
}

void sem_init(int semId, int index, int value)
{
    union semun semValue;
    semValue.val = value;
    semctl(semId, index, SETVAL, semValue);
}

void sem_p(int semId, int index)
{
    struct sembuf sops[1];
    sops->sem_num = index;
    sops->sem_op=-1;
    sops->sem_flg = 0;
    semop(semId, sops, 1);
}

void sem_v(int semId, int index)
{
    struct sembuf sops[1];
    sops->sem_num = index;
    sops->sem_op = +1;
    sops->sem_flg = 0;
    semop(semId, sops, 1);
}

// #include <sys/sem.h>
// int semget(key_t key, int nsems, int semflg);

// #include <sys/sem.h>

// int semctl(int semid, int semnum, int op, ...);

// union semun
// {
//     int val;               /* Value for SETVAL */
//     struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
//     unsigned short *array; /* Array for GETALL, SETALL */
//     struct seminfo *__buf; /* Buffer for IPC_INFO
//                               (Linux-specific) */
// };

// #include <sys/sem.h>
// int semop(int semid, struct sembuf *sops, size_t nsops);

// struct sembuf sops[2];
// int semid;

// /* Code to set semid omitted */

// sops[0].sem_num = 0; /* Operate on semaphore 0 */
// sops[0].sem_op = 0;  /* Wait for value to equal 0 */
// sops[0].sem_flg = 0;