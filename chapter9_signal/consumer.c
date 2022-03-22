#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
void init();
int sem_id;
int main(int argc, char *argv[])
{
    struct sembuf sops[2];
    /*set operate way for sem*/
    sops[0].sem_num = 0;
    sops[0].sem_op = -1;
    // P 操作，表示有多少个产品可以消费（相当于生产了多少个产品）
    sops[0].sem_flg = 0;
    sops[1].sem_num = 1;
    sops[1].sem_op = 1;
    // V 操作，表示还可以生成的产品数
    sops[1].sem_flg = 0;
    init();
    printf("this is a customer\n");
    while (1)
    {
        printf("\n\nbefore consume\n");
        printf("customer number is %d\n", semctl(sem_id, 0, GETVAL));
        printf("space number is %d\n", semctl(sem_id, 1, GETVAL));
        semop(sem_id, &sops[0], 1);
        printf("now consume .....\n");
        semop(sem_id, &sops[1], 1);
        printf("space number is %d\n", semctl(sem_id, 1, GETVAL));
        printf("customer number is %d\n", semctl(sem_id, 0, GETVAL));
        sleep(1);
    }
}
void init()
{
    sem_id = semget((key_t)1234, 2, IPC_CREAT | 0644); /*get semaphore include two sem*/
}