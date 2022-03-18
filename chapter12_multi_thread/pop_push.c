#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void CleanFunc(void *pArg)
{
    printf("CleanFunc(%d)\n", (int)pArg);
}
void *ThreadFunc(void *pArg)
{
    pthread_cleanup_push(CleanFunc, (void *)1);
    pthread_cleanup_push(CleanFunc, (void *)2);
    sleep(2);
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
int main()
{
    pthread_t thdId;
    pthread_create(&thdId, NULL, ThreadFunc, (void *)2);
    pthread_join(thdId, NULL);
    return 0;
}