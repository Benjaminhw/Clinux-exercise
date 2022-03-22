#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
int g_iSeq = 0;
void SignHandler(int iSignNo)
{
    int iSeq = g_iSeq++;
    printf("%d Enter SignHandler,signo:%d\n", iSeq, iSignNo);
    sleep(3);
    printf("%d Leave SignHandler,signo:%d\n", iSeq, iSignNo);
}
int main()
{
    char szBuf[8];
    int iRet;
    signal(SIGINT, SignHandler);
    //不同的信号调用同一个处理函数
    signal(SIGQUIT, SignHandler);
    do
    {
        iRet = read(STDIN_FILENO, szBuf, sizeof(szBuf) - 1);
        if (iRet < 0)
        {
            perror("read fail.");
            break;
        }
        szBuf[iRet] = 0;
        printf("Get: %s", szBuf);
    } while (strcmp(szBuf, "quit\n") != 0);
    return 0;
}