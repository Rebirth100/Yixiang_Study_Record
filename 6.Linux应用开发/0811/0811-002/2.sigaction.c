#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
void getSignalDoAction(int, siginfo_t *, void *);
int main()
{
    struct sigaction action;
    bzero(&action, sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = getSignalDoAction;

    for (int i = 1; i < 8; i++)
    {
        sigaction(i, &action, NULL);
        fprintf(stderr, "信号[%d]的处理函数注册完毕\n", i);
        usleep(120000);
    }

    int pid = getpid();
    while (1)
    {
        fprintf(stderr, "大家好![%d]\n", pid);
        sleep(1);
    }
}

void getSignalDoAction(int sigNum, siginfo_t *info, void *args)
{
    fprintf(stderr, "收到信号:%d\n", sigNum);
    uid_t uid = info->si_uid;
    pid_t pid = info->si_pid;
    struct passwd *pwd = getpwuid(uid);
    for (int i = 0; i < 10; i++)
    {
        if (info && pwd)
        {
            fprintf(stderr, "Hello,%s, 您通过%d给我发了数据%d???\n",
                    pwd->pw_name, pid, info->si_int);
            if (sigNum == 7)
            {
                fprintf(stderr,"Hello,%s, 收到退出指令\n",pwd->pw_name);
                int exitTime=info->si_int;
                while(exitTime>0)
                {
                    fprintf(stderr, "程序将在(%d)后退出\n", exitTime);
                    sleep(1);
                    --exitTime;
                }
            
                exit(0);
            }
        }
        usleep(300000);
    }
}

// #include <signal.h>
// int sigaction(int signum,
//               const struct sigaction *_Nullable restrict act,
//               struct sigaction *_Nullable restrict oldact);
// struct sigaction
// {
//     void (*sa_handler)(int);
//     void (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t sa_mask;
//     int sa_flags;
//     void (*sa_restorer)(void);
// };

// siginfo_t
// {
//     int si_signo;          /* Signal number */
//     int si_errno;          /* An errno value */
//     int si_code;           /* Signal code */
//     int si_trapno;         /* Trap number that caused
//                               hardware-generated signal
//                               (unused on most architectures) */
//     pid_t si_pid;          /* Sending process ID */
//     uid_t si_uid;          /* Real user ID of sending process */
//     int si_status;         /* Exit value or signal */
//     clock_t si_utime;      /* User time consumed */
//     clock_t si_stime;      /* System time consumed */
//     union sigval si_value; /* Signal value */
//     int si_int;            /* POSIX.1b signal */
//     void *si_ptr;          /* POSIX.1b signal */
//     int si_overrun;        /* Timer overrun count;
//                               POSIX.1b timers */
//     int si_timerid;        /* Timer ID; POSIX.1b timers */
//     void *si_addr;         /* Memory location which caused fault */
//     long si_band;          /* Band event (was int in
//                               glibc 2.3.2 and earlier) */
//     int si_fd;             /* File descriptor */
//     short si_addr_lsb;     /* Least significant bit of address
//                               (since Linux 2.6.32) */
//     void *si_lower;        /* Lower bound when address violation
//                               occurred (since Linux 3.19) */
//     void *si_upper;        /* Upper bound when address violation
//                               occurred (since Linux 3.19) */
//     int si_pkey;           /* Protection key on PTE that caused
//                               fault (since Linux 4.6) */
//     void *si_call_addr;    /* Address of system call instruction
//                               (since Linux 3.5) */
//     int si_syscall;        /* Number of attempted system call
//                               (since Linux 3.5) */
//     unsigned int si_arch;  /* Architecture of attempted system call
//                               (since Linux 3.5) */
// }


//exec