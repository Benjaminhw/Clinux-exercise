#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
void *thread_function(void *arg);
char message[] = "Hello World";
int thread_finished = 0;
int main()
{
    int res = 0;
    pthread_t a_thread;
    void *thread_result;
    pthread_attr_t thread_attr; //定义属性
    struct sched_param scheduling_value;
    res = pthread_attr_init(&thread_attr); //属性初始化
    if (res != 0)
    {
        perror("Attribute creation failed");
        exit(EXIT_FAILURE); // EXIT_FAILURE -1
    }
    //设置调度策略
    res = pthread_attr_setschedpolicy(&thread_attr, SCHED_OTHER);
    if (res != 0)
    {
        perror("Setting schedpolicy failed");
        exit(EXIT_FAILURE);
    }
    //设置脱离状态
    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    //创建线程
    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    //获取最大优先级别
    int max_priority = sched_get_priority_max(SCHED_OTHER);
    //获取最小优先级
    int min_priority = sched_get_priority_min(SCHED_OTHER);
    //重新设置优先级别
    scheduling_value.sched_priority = min_priority + 5;
    //设置优先级别
    res = pthread_attr_setschedparam(&thread_attr, &scheduling_value);
    pthread_attr_destroy(&thread_attr);
    while (!thread_finished)
    {
        printf("Waiting for thread to say it's finished...\n");
        sleep(1);
    }
    printf("Other thread finished, bye!\n");
    exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}