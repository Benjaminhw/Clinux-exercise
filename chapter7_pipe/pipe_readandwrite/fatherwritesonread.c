#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fds[2] = {0};
    pipe(fds);
    char szBuf[32] = {'\0'};
    if (fork() == 0)
    {
        //表示子进程
        close(fds[1]); //子进程关闭写
        sleep(2);
        //确保父进程有时间关闭读，并且往管道中写内容
        if (read(fds[0], szBuf, sizeof(szBuf)) > 0)
            puts(szBuf);
        close(fds[0]); //子关闭读
        exit(0);
    }
    else
    {
        //表示父进程
        close(fds[0]); //父关闭读
        write(fds[1], "hello", 6);
        waitpid(-1, NULL, 0);
        //等子关闭读
        //write(fds[1], "world", 6);
        //此时将会出现“断开的管道”因为子的读已经关闭了
        close(fds[1]); //父关闭写
        exit(0);
    }
    return 0;
}
