#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_SIZE  128
struct msgbuf
{
    long mtype;    /* message type, must be > 0 */
    char mtext[MSG_SIZE]; /* message data */
};
int main()
{
    key_t key = ftok(".", 1109);
    if (key == -1)
    {
        perror("ftok错误");
        return 0;
    }
    fprintf(stderr, "key:%#x\n", key);
    int msgId = msgget(key, IPC_CREAT | 0620);
    if (msgId == -1)
    {
        perror("msgget错误");
        return 0;
    }
    fprintf(stderr, "msgId:%#x\n", msgId);

    int index=100;
    struct msgbuf   msg;
    while (1)
    {
        bzero(&msg,sizeof(msg));
        msg.mtype=index;
        puts("请输入内容:");
        fgets(msg.mtext,MSG_SIZE,stdin);
        msg.mtext[strlen(msg.mtext)-1]='\0';
        if(msgsnd(msgId,&msg,strlen(msg.mtext),0)==0)
        {
            fprintf(stderr,"消息[%ld]:%s已发送\n", msg.mtype,msg.mtext);
            index++;
        }
    }
    
}

//////////////////msgget//////////////////////
// #include <sys/msg.h>
// int msgget(key_t key, int msgflg);

// #include <sys/msg.h>

// int msgsnd(int msqid, const void msgp[.msgsz], size_t msgsz,int msgflg);

// ssize_t msgrcv(int msqid, void msgp[.msgsz], size_t msgsz, long msgtyp, int msgflg);

// struct msgbuf
// {
//     long mtype;    /* message type, must be > 0 */
//     char mtext[1]; /* message data */
// };