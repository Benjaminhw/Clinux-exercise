#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>
void *threadfunc(void *args)
{
    char *p = (char *)malloc(10);
    //自己分配了内存
    int i = 0;
    for (; i < 10; i++)
    {
        printf("hello,my name is wangxiao!\n");
        sleep(1);
    }
    free(p);
    //如果父线程中没有调用 pthread_cancel，此处可以执行
    printf("p is freed\n");
    pthread_exit((void *)3);
}
int main()
{
    pthread_t pthid;
    pthread_create(&pthid, NULL, threadfunc, NULL);
    int i = 1;
    for (; i < 5; i++)
    /*父线程的运行次数比子线程的要少，当父线程结束的时候，如果没有pthread_join 函数等待子线程执行的话，子线程也会退出*/
    {
        printf("hello,nice to meet you!\n");
        sleep(1);
        // if(i % 3 == 0)
        // pthread_cancel(pthid);
        /*表示当 i%3==0 的时候就取消子线程，该函数将导致子线程直接退出，不会执行上面紫色的 free 部分的代码，即释放空间失败。要想释放指针类型的变量p，此时必须要用 pthread_cleanup_push 和pthread_cleanup_pop 函数释放空间，见后面的例子*/
    }
    long retvalue = 0;
    pthread_join(pthid, (void **)&retvalue); //等待子线程释放空间，并获取子线程的返回值
    printf("return value is :%ld\n", retvalue);
    return 0;
}
