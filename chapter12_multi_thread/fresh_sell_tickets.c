#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int ticketcount = 10;
pthread_mutex_t lock; //互斥锁
pthread_cond_t cond;  //条件变量
void *salewinds1(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock); //因为要访问全局的共享变量 ticketcount，所以就要加锁
        if (ticketcount > 0)       //如果有票
        {
            printf("windows1 start sale ticket!the ticket is:%d\n", ticketcount);
            ticketcount--; //则卖出一张票
            if (ticketcount == 0)
                pthread_cond_signal(&cond); //通知没有票了
            printf("sale ticket finish!,the last ticket is:%d\n", ticketcount);
        }
        else //如果没有票了，就解锁退出
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
        sleep(1); //要放到锁的外面
    }
}
void *salewinds2(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        if (ticketcount > 0)
        {
            printf("windows2 start sale ticket!the ticket is:%d\n", ticketcount);
            ticketcount--;
            if (ticketcount == 0)
                pthread_cond_signal(&cond); //发送信号
            printf("sale ticket finish!,the last ticket is:%d\n", ticketcount);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}
void *setticket(void *args) //重新设置票数
{
    pthread_mutex_lock(&lock); //因为要访问全局变量 ticketcount，所以要加锁
    if (ticketcount > 0)
        pthread_cond_wait(&cond, &lock); //如果有票就解锁并阻塞，直到没有票就执行下面的
    ticketcount = 10;                    //重新设置票数为 10
    pthread_mutex_unlock(&lock);         //解锁
    sleep(1);
    pthread_exit(NULL);
}
int main()
{
    pthread_t pthid1, pthid2, pthid3;
    pthread_mutex_init(&lock, NULL);                 //初始化锁
    pthread_cond_init(&cond, NULL);                  //初始化条件变量
    pthread_create(&pthid1, NULL, salewinds1, NULL); //创建线程
    pthread_create(&pthid2, NULL, salewinds2, NULL);
    pthread_create(&pthid3, NULL, setticket, NULL);
    pthread_join(pthid1, NULL); //等待子线程执行完毕
    pthread_join(pthid2, NULL);
    pthread_join(pthid3, NULL);
    pthread_mutex_destroy(&lock); //销毁锁
    pthread_cond_destroy(&cond);  //销毁条件变量
}
