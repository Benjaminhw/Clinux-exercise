//消息接收
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#define BUFFER 255
struct msgtype
{
    //重定义消息结构体
    long mtype;
    char buffer[BUFFER + 1];
};
int main()
{
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    //获得消息队列
    if (msgid == -1)
    {
        fprintf(stderr, "Creat Message Error:%s\a\n", strerror(errno));
        exit(1);
    }
    struct msgtype msg;
    memset(&msg, 0, sizeof(struct msgtype));
    while (1)
    {
        msgrcv(msgid, &msg, sizeof(msg.buffer), 1, 0); //接收消息
        fprintf(stdout, "Server Receive:%s\n", msg.buffer);
        msg.mtype = 2;
        strncpy(msg.buffer, "world", BUFFER);
        msgsnd(msgid, &msg, sizeof(msg.buffer), 0);
        //发送消息
    }
    exit(0);
}
