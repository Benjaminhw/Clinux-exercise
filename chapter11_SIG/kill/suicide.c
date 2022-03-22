#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    while (1)
    {
        if (getchar() == EOF)
            //运行之后输入没有反应，当按下 Ctrl+d（EOF），进程关闭
            kill(getpid(), SIGQUIT);
    }
    return 0;
}