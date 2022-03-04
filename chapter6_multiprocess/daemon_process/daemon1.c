#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
int main()
{
    int i = 0;
    if (fork()> 0)
        exit(0);
    setsid();
    chdir("/");
    umask(0);
    for (; i < 64; i++)
    {
        close(i);
    }
    i = 0;
    while (i < 10)
    {
        printf("%d\n", i);
        time_t ttime;
        time(&ttime);
        struct tm *pTm = gmtime(&ttime);
        syslog(LOG_INFO, "%d %04d:%02d:%02d", i, (1900 + pTm->tm_year), (1 + pTm -> tm_mon), (pTm->tm_mday));
        i++;
        sleep(2);
    }
}
//记录的信息可以查看vi /var/log/syslog