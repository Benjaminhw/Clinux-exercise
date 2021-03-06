#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
union semun
//必须重写这个共用体
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int main()
{
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); //创建信号量集
    if (semid == -1)
    {
        perror("semget error");
        exit(-1);
    }
    if (fork() == 0) //表示子进程
    {
        struct sembuf sem; //定义信号量结构体
        memset(&sem, 0, sizeof(struct sembuf));
        sem.sem_num = 0; //信号量的编号,第一个为 0
        sem.sem_op = 1;  //+1 表示执行 V 操作,生产产品
        sem.sem_flg = 0; //或写 SEM_UNDO
        union semun arg;
        arg.val = 0;                   //初始化数据
        semctl(semid, 0, SETALL, arg); //将数据全部设置到信号量集里面去,相当于公共数据
        while (1)
        {
            semop(semid, &sem, 1);                                           //执行指定的 V 操作,表示生产产品
            printf("productor total number:%d\n", semctl(semid, 0, GETVAL)); //获得公共值
            sleep(1);
        }
    }
    else
    {
        sleep(2);          //先让子进程有时间生产
        struct sembuf sem; //定义信号量结构体
        memset(&sem, 0, sizeof(struct sembuf));
        sem.sem_num = 0; //信号量的编号,第一个为 0
        sem.sem_op = -1; //-1 表示执行 P 操作,消费产品
        sem.sem_flg = 0; //或写 SEM_UNDO
        while (1)
        {
            semop(semid, &sem, 1);                                          //执行指定的 P 操作消费产品
            printf("costomer total number:%d\n", semctl(semid, 0, GETVAL)); //获得公共值
            sleep(2);
        }
    }
}