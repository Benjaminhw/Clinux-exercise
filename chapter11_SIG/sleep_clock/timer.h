struct itimerval
{
    struct timeval it_interval; /* next value */
    //重复间隔
    struct timeval it_value; /* current value */
    //初始间隔
};
struct timeval
{
    long tv_sec;
    /* seconds */
    //时间的秒数部分
    long tv_usec;
    /* microseconds */
    //时间的微秒部分
}