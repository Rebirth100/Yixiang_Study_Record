#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/wait.h>
int main()
{
    int status = 0;
    pid_t pid = fork();
    if (pid > 0)
    {
        status=-1;
        //wait(&status);
        waitpid(pid,&status,0);
        fprintf(stderr, "父进程退出  子进程[%d]的退出状态%d\n",pid,WEXITSTATUS(status));
        exit(0);
    }

    if (pid == 0)
    {
        fprintf(stderr, "子进程开始干活");
        // execl("/usr/bin/ls","./app","/home","/","-d",NULL);
        // execlp("ls","ls","/home","/","-l",NULL);\

        // char *argv[]={"ls","/home","/","-l",NULL};
        // execv("/usr/bin/ls",argv);

        // char *argv[]={"ls","/home","/","-l",NULL};
        // execvp("ls",argv);

        char *argv[] = {"info","/","/dev","/" ,NULL};
        execvp("info", argv);
    }
}

// #include <sys/wait.h>
// pid_t wait(int *_Nullable wstatus);
// pid_t waitpid(pid_t pid, int *_Nullable wstatus, int options);

