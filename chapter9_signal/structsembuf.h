struct sembuf
{
    short sem_num; //操作信号量在信号量集合中的编号，第一个信号量的编号是 0。
    short sem_op;  /*sem_op 成员的值是信号量在一次操作中需要改变的数值。通常只会用到两个值，一个是-1，也就是 p 操作，它等待信号量变为可用；一个是+1，也就是 v 操作，它发送信号通知信号量现在可用。*/
    short sem_flg; //通常设为：SEM_UNDO，程序结束，信号量为semop调用前的值。
};

union semun{ 
	int val; /* Value for SETVAL */ 
	struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */ 
	unsigned short *array; /* Array for GETALL, SETALL */ 
};

struct semid_ds
{
    struct ipc_perm sem_perm; /* Ownership and permissions */
    time_t sem_otime;         /* Last semop time */
    time_t sem_ctime;         /* Last change time */
    unsigned long sem_nsems;  /* No. of semaphores in set */
} ;

struct ipc_perm
{
    key_t __key;          /* Key supplied to semget(2) */
    uid_t uid;            /* Effective UID of owner */
    gid_t gid;            /* Effective GID of owner */
    uid_t cuid;           /* Effective UID of creator */
    gid_t cgid;           /* Effective GID of creator */
    unsigned short mode;  /* Permissions */
    unsigned short __seq; /* Sequence number */
};