#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <pwd.h>
int main()
{
    // 忽略挂断信号
    signal(SIGHUP, SIG_IGN);

    // 开启新的进程(父进程退出，子进程开启新的会话)
    pid_t pid = fork();
    if (pid == -1)
    {
        exit(0);
    }
    // 父进程退出
    if (pid > 0)
    {
        exit(0);
    }

    // 子进程继续
    pid = setsid(); // 开启新的会话
    if (pid == -1)
    {
        exit(0);
    }
    pid = fork();
    if (pid == -1)
    {
        exit(0);
    }
    // 父进程退出
    if (pid > 0)
    {
        exit(0);
    }
    // 让三代子孙成为进程组长
    pid = setpgrp();
    if (pid == -1)
    {
        exit(0);
    }

    // 禁止交互
    int maxFd = sysconf(_SC_OPEN_MAX);
    for (int i = 0; i < maxFd; i++)
    {
        close(i);
    }

    // 切换工作目录到一个不可卸载的目录
    chdir("/");
    umask(0);

    // 执行业务
    int index = 1000;
    uid_t currentUid = getuid();
    struct passwd *pwd = getpwuid(currentUid);
    while (1)
    {
        // syslog(LOG_DAEMON,"Hello!user %d\n",index++);
        time_t curr_time = time(NULL);
        struct tm *currentTime = localtime(&curr_time);

        syslog(LOG_INFO,
               "file:%s uid:%d user: %s setMessage:Hello(%d) onTime:%d-%d-%d %d:%d:%d\n",
               __FILE__,
               currentUid,
               pwd->pw_name,
               index++,
               currentTime->tm_year + 1900,
               currentTime->tm_mon + 1,
               currentTime->tm_mday,
               currentTime->tm_hour,
               currentTime->tm_min,
               currentTime->tm_sec);
        // syslog(LOG_DAEMON,
        //         "file:%s uid:%d user: %s setMessage:Hello(%d) onTime:%d-%d-%d %d:%d:%d\n",
        //         __FILE__,
        //         currentUid,
        //         pwd->pw_name,
        //         index++,
        //         currentTime->tm_year + 1900,
        //         currentTime->tm_mon + 1,
        //         currentTime->tm_mday,
        //         currentTime->tm_hour,
        //         currentTime->tm_min,
        //         currentTime->tm_sec);
        sleep(10);
    }
}

// #include <unistd.h>
// pid_t setsid(void);

// #include <unistd.h>
// int setpgid(pid_t pid, pid_t pgid);
// pid_t getpgid(pid_t pid);
// pid_t getpgrp(void);                     /* POSIX.1 version */
// pid_t getpgrp(pid_t pid); /* BSD version */
// int setpgrp(void);                                 /* System V version */
// int setpgrp(pid_t pid, pid_t pgid); /* BSD version */

// #include <syslog.h>
// void openlog(const char *ident, int option, int facility);
// void syslog(int priority, const char *format, ...);
// void closelog(void);


//录屏作业:
//讲解守护进程的开发流程 