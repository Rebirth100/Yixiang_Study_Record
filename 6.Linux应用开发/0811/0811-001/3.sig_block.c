#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
void getSignal(int);
int main()
{
    pid_t pid = getpid();
    for (int i = 1; i <= 64; i++)
    {
        if (i == 31 || i == 32)
        {
            continue;
        }
        // 注册偶数信号处理函数
        signal(i, getSignal);
        fprintf(stderr, "注册信号%d处理函数\n", i);
    }

    sleep(3);
    // 时间小于30秒时，阻塞1~10的信号，延迟到30秒以后执行
    sigset_t set;
    sigemptyset(&set);
    for (int i = 1; i <= 10; i++)
    {
        sigaddset(&set, i);
    }
    for (int i = 60; i <= 64; i++)
    {
        sigaddset(&set, i);
    }
    sigprocmask(SIG_BLOCK, &set, NULL);
    fprintf(stderr, "信号1~10阻塞中\n");

    int n = 0;
    while (1)
    {
        fprintf(stderr, "我是[%d] 启动了:%d秒\n", pid, ++n);
        if (n < 30)
        {
            fprintf(stderr, "信号1~10阻塞中\n");
        }
        if (n == 30)
        {
            sigprocmask(SIG_UNBLOCK, &set, NULL);
            fprintf(stderr, "信号1~10解除阻塞\n");
        }
        sleep(1);
    }
}

void getSignal(int sig)
{
    fprintf(stderr, "收到信号:%d\n", sig);
    for (int i = 0; i < 20; i++)
    {
        fprintf(stderr, "#");
        usleep(10000);
    }
    fprintf(stderr, "\n\n");
}

/*****************sigset_t 信号集操作********************** */
// #include <signal.h>

// int sigemptyset(sigset_t *set);
// int sigfillset(sigset_t *set);

// int sigaddset(sigset_t *set, int signum);
// int sigdelset(sigset_t *set, int signum);

// int sigismember(const sigset_t *set, int signum);

/******************sigprocmask*********************** */
// #include <signal.h>
// int sigprocmask(int how, const sigset_t *_Nullable restrict set,
//                                   sigset_t *_Nullable restrict oldset);
