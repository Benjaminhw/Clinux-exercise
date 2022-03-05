#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) //演示通过命令行传递参数
{
    if (argc != 2)
    {
        puts("Usage: MkFifo.exe {filename}");
        return -1;
    }
    if (mkfifo(argv[1], 0666) == -1)
    {
        perror("mkfifo fail");
        return -2;
    }
    return 0;
}