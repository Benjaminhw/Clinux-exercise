#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void SignHandler(int iSignNo)
{
    printf("signal:%d\n", iSignNo);
}
int main()
{
    signal(SIGALRM, SignHandler);
    alarm(3);
    //等待 3 秒之后自动产生 SIGALRM 信号
    printf("Before pause().\n");
    pause();
    //将进程挂起，直到有信号发生才退出挂起状态
    printf("After pause().\n");
    return 0;
}