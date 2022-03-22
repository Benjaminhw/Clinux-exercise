struct sigaction
{
    void (*sa_handler)(int);
    //老类型的信号处理函数指针
    void (*sa_sigaction)(int, siginfo_t *, void *); //新类型的信号处理函数指针
    sigset_t sa_mask;
    //将要被阻塞的信号集合
    int sa_flags;
    //信号处理方式掩码 (  SA_SIGINFO )
    void (*sa_restorer)(void);
    //保留，不要使用
};