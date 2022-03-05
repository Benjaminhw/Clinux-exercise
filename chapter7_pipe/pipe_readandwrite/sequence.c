#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fds[2];
    pipe(fds);
    //注释掉这部分将导致写进程被信号SIGPIPE终止
    sigset_t setSig;
    sigemptyset(&setSig);
    sigaddset(&setSig, SIGPIPE);
    sigprocmask(SIG_BLOCK, &setSig, NULL);
    char szBuf[10] = {0};
    if (fork() == 0)
    {
        close(fds[1]); //子关闭写
        sleep(2);      //确保父关闭读
        if (read(fds[0], szBuf, sizeof(szBuf)) > 0)
            puts(szBuf);
        close(fds[0]); //子关闭读
    }
    else
    {
        close(fds[0]); //父关闭读
        write(fds[1], "hello", 6);
        wait(NULL);
        write(fds[1], "world", 6); //子的读关闭，父还在写
        close(fds[1]);             //父关闭写
    }
    return 0;
}
