#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void ThreadClean(void *arg)
{
    pthread_mutex_unlock(&mutex);
}
void *child1(void *arg)
{
    pthread_cleanup_push(ThreadClean,NULL); //1
    while (1)
    {
        printf("thread 1 get running.\n");
        printf("thread 1 pthread_mutex_lock returns %d\n", pthread_mutex_lock(&mutex));
        pthread_cond_wait(&cond, &mutex); //等待父进程发送信号
        printf("thread 1 condition applied\n");
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    pthread_cleanup_pop(0); //2
    return 0;
}
void *child2(void *arg)
{
    while (1)
    {
        sleep(3); // 3
        printf("thread 2 get running.\n");
        printf("thread 2 pthread_mutex_lock returns %d\n", pthread_mutex_lock(&mutex));
        pthread_cond_wait(&cond, &mutex);
        printf("thread 2 condition applied\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main(void)
{
    pthread_t tid1, tid2;
    printf("hello, condition variable test\n");
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&tid1, NULL, child1, NULL);
    pthread_create(&tid2, NULL, child2, NULL);
    while (1)
    {                         //父线程
        sleep(2);             // 4
        pthread_cancel(tid1); // 5
        sleep(2);             // 6
        pthread_cond_signal(&cond);
    }
    sleep(10);
    return 0;
}
