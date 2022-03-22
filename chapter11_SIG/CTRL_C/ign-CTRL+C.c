#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
    signal(SIGINT, SIG_IGN);
    while (1)
        sleep(1);
    return 0;
}