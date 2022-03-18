#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define BUFFER_SIZE 16 //表示一次最多可以不间断的生产 16 个产品
struct prodcons
{
    int buffer[BUFFER_SIZE]; /* 数据 */
    pthread_mutex_t lock;    /* 加锁 */
    int readpos, writepos;   /* 读 pos 写位置 */
    pthread_cond_t notempty; /* 不空，可以读 */
    pthread_cond_t notfull;  /* 不满，可以写 */
};
/* 初始化*/
void init(struct prodcons *b)
{
    pthread_mutex_init(&b->lock, NULL);    //初始化锁
    pthread_cond_init(&b->notempty, NULL); //初始化条件变量
    pthread_cond_init(&b->notfull, NULL);  //初始化条件变量
    b->readpos = 0;                        //初始化读取位置从 0 开始
    b->writepos = 0;                       //初始化写入位置从 0 开始
}
/* 销毁操作 */
void destroy(struct prodcons *b)
{
    pthread_mutex_destroy(&b->lock);
    pthread_cond_destroy(&b->notempty);
    pthread_cond_destroy(&b->notfull);
}
void put(struct prodcons *b, int data) //生产者
{
    pthread_mutex_lock(&b->lock);
    while ((b->writepos + 1) % BUFFER_SIZE == b->readpos)
    { //判断是不是满了
        printf("wait for not full\n");
        pthread_cond_wait(&b->notfull, &b->lock); //此时为满，不能生产，等待不满的信号
    }
    //下面表示还没有满，可以进行生产
    b->buffer[b->writepos] = data;
    b->writepos++; //写入点向后移一位
    if (b->writepos >= BUFFER_SIZE)
        b->writepos = 0;               //如果到达最后，就再转到开头
    pthread_cond_signal(&b->notempty); //此时有东西可以消费，发送非空的信号
    pthread_mutex_unlock(&b->lock);
}
int get(struct prodcons *b) //消费者
{
    pthread_mutex_lock(&b->lock);
    while (b->writepos == b->readpos)
    { //判断是不是空
        printf("wait for not empty\n");
        pthread_cond_wait(&b->notempty, &b->lock); //此时为空，不能消费，等待非空信号
    }
    //下面表示还不为空，可以进行消费
    int data = b->buffer[b->readpos];
    b->readpos++; //读取点向后移一位
    if (b->readpos >= BUFFER_SIZE)
        b->readpos = 0;               //如果到达最后，就再转到开头
    pthread_cond_signal(&b->notfull); //此时可以进行生产，发送不满的信号
    pthread_mutex_unlock(&b->lock);
    return data;
}
/*--------------------------------------------------------*/
#define OVER (-1)       //定义结束标志
struct prodcons buffer; //定义全局变量
/*--------------------------------------------------------*/
void *producer(void *data)
{
    int n = 0;
    for (; n < 50; n++)
    {
        printf(" put-->%d\n", n);
        put(&buffer, n);
    }
    put(&buffer, OVER);
    printf("producer stopped!\n");
    pthread_exit(NULL);
}
/*--------------------------------------------------------*/
void *consumer(void *data)
{
    while (1)
    {
        int d = get(&buffer);
        if (d == OVER)
            break;
        printf(" %d-->get\n", d);
    }
    printf("consumer stopped!\n");
    pthread_exit(NULL);
}
/*--------------------------------------------------------*/
int main(void)
{
    pthread_t th_a, th_b;
    init(&buffer);
    pthread_create(&th_a, NULL, producer, 0);
    pthread_create(&th_b, NULL, consumer, 0);
    pthread_join(th_a, NULL);
    pthread_join(th_b, NULL);
    destroy(&buffer);
    return 0;
}
