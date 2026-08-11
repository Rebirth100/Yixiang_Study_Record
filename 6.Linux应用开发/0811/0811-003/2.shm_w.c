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
    fprintf(stderr, "获得共享内存%d\n", shmID);
    char *message = shmat(shmID, NULL, 0);
    if (message == NULL)
    {
        return 0;
    }
    fprintf(stderr, "共享映射完毕 message:%p\n", message);
    bzero(message, SHM_SIZE);
    while (1)
    {
        sprintf(message, "Hello#%d\n", rand() % 1000 + 1000);
        sleep(3);
    }

    return 0;
}