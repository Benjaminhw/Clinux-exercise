#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/stat.h> 
#include <sys/wait.h>//对应wait 原文缺少
#include <unistd.h>//sleep

struct MSG
{
    long mtype;
    char buf[64];
};
int main()
{
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget error");
        exit(-1);
    }
    struct MSG msg;
    memset(&msg, 0, sizeof(struct MSG));
    if (fork() > 0)
    {
        msg.mtype = 1;
        strcpy(msg.buf, "hello");
        msgsnd(msgid, &msg, sizeof(msg.buf), 0);
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
        exit(0);
    }
    else
    {
        sleep(2);
        //让父进程有时间往消息队列里面写
        msgrcv(msgid, &msg, sizeof(msg.buf), 1, 0);
        puts(msg.buf);
        exit(0);
    }
}
