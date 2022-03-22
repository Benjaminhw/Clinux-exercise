#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void handle(int signo)
{
    printf("signo: %d\n", signo);
}
int main()
{
    struct sigaction st;
    st.sa_handler = handle;
    st.sa_flags = 0;
    sigaction(SIGINT, &st, NULL);
    while (1)
    {
        sleep(1);
    }
}