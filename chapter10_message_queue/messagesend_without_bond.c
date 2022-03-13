#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#define BUFFER 255
struct msgtype
{
    //重新定义该结构体
    long mtype;
    //第一个参数不变
    char buffer[BUFFER + 1];
};
int main(int argc, char **argv)
{
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT); //获取消息队列
    if (msgid == -1)
    {
        fprintf(stderr, "Creat Message Error:%s\a\n", strerror(errno));
        exit(1);
    }
    struct msgtype msg;
    memset(&msg, 0, sizeof(struct msgtype));
    msg.mtype = 1;
    //给结构体的成员赋值
    strncpy(msg.buffer, "hello", BUFFER);
    msgsnd(msgid, &msg, sizeof(msg.buffer), 0); //发送信号
    memset(&msg, 0, sizeof(msg));
    //清空结构体
    msgrcv(msgid, &msg, sizeof(msg.buffer), 2, 0); //接收信号
    fprintf(stdout, "Client receive:%s\n", msg.buffer);
    exit(0);
}
