#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *ThreadFunc(void *pArg) //参数的值为 123
{
    int i = 0;
    for (; i < 10; i++)
    {
        printf("Hi,I'm child thread,arg is:%ld\n", (long)pArg);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t thdId;
    pthread_create(&thdId, NULL, ThreadFunc, (void *)123);
    int i = 0;
    for (; i < 10; i++)
    {
        printf("Hi,I'm main thread,child thread id is:%lx\n", thdId);
        sleep(1);
    }
    return 0;
}