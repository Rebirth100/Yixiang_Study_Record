#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
int main()
{

    while (1)
    {
        int targetPid;
        fprintf(stderr, "请输入目标进程:");
        scanf("%d", &targetPid);
        for (int signalNum = 1; signalNum <= 8; signalNum++)
        {
            if (kill(targetPid, signalNum) == -1)
            {
                perror("信号发送失败");
                continue;
            }
            fprintf(stderr, "向%d发送信号%d成功\n", targetPid, signalNum);
        }
        sleep(3);
        for (int signalNum = 64; signalNum >= 60; signalNum--)
        {
            if (kill(targetPid, signalNum) == -1)
            {
                perror("信号发送失败");
                continue;
            }
            fprintf(stderr, "向%d发送信号%d成功\n", targetPid, signalNum);
        }
    }
}

// #include <signal.h>
// int kill(pid_t pid, int sig);