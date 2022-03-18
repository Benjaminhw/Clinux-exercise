#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ticketcount = 20;        //火车票，公共资源（全局）
void *salewinds1(void *args) //售票口 1
{
    while (ticketcount > 0) //如果有票,则卖票
    {
        printf("windows1 start sale ticket!the ticket is:%d\n", ticketcount);
        sleep(3);      //卖一张票需要 3 秒的操作时间
        ticketcount--; //出票
        printf("sale ticket finish!,the last ticket is:%d\n", ticketcount);
    }
}
void *salewinds2(void *args) //售票口 2
{
    while (ticketcount > 0) //如果有票,则卖票
    {
        printf("windows2 start sale ticket!the ticket is:%d\n", ticketcount);
        sleep(3);      //卖一张票需要 3 秒的操作时间
        ticketcount--; //出票
        printf("sale ticket finish!,the last ticket is:%d\n", ticketcount);
    }
}
int main()
{
    pthread_t pthid1 = 0;
    pthread_t pthid2 = 0;
    pthread_create(&pthid1, NULL, salewinds1, NULL); //线程 1
    pthread_create(&pthid2, NULL, salewinds2, NULL); //线程 2
    pthread_join(pthid1, NULL);
    pthread_join(pthid2, NULL);
    return 0;
}