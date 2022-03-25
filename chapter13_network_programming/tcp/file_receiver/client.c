/* TCP 文件接收客户端 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#define FILE_MAX_LEN 64
#define DEFAULT_SVR_PORT 2828
int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[1024], filename[FILE_MAX_LEN + 1];
    char ip_addr[64];
    struct hostent *he;
    struct sockaddr_in their_addr;
    int i = 0, len, total;
    unsigned short port;
    FILE *file = NULL;
    if (argc < 2)
    {
        printf("need a server ip \n");
        exit;
    }
    strncpy(ip_addr, argv[1], sizeof(ip_addr));
    port = DEFAULT_SVR_PORT;
    if (argc >= 3)
    {
        port = (unsigned short)atoi(argv[2]);
    }
    //做域名解析(DNS)
    // he = gethostbyname(argv[1]);
    //第一步:建立一个 TCP 套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    //第二步:设置服务器地址和端口 2828
    memset(&their_addr, 0, sizeof(their_addr));
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr.s_addr = inet_addr(ip_addr);
    // their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    // bzero(&(their_addr.sin_zero),8);
    printf("connect server %s:%d\n", ip_addr, port);
    /*第三步:用 connect 和服务器建立连接 ,注意,这里没有使用本地端口,将由协议栈自动分配一个端口*/
    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    if (send(sockfd, "hello", 6, 0) < 0)
    {
        perror("send ");
        exit(1);
    }
    /* 接收文件名,为编程简单,假设前 64 字节固定是文件名,不足用 0 来增充 */
    total = 0;
    while (total < FILE_MAX_LEN)
    {
        /* 注意这里的接收 buffer 长度,始终是未接收文件名剩下的长度,*/
        len = recv(sockfd, filename + total, (FILE_MAX_LEN - total), 0);
        if (len <= 0)
            break;
        total += len;
    }
    /* 接收文件名出错 */
    if (total != FILE_MAX_LEN)
    {
        perror("failure file name");
        exit(-3);
    }
    printf("recv file %s.....\n", filename);
    file = fopen(filename, "wb");
    // file = fopen("/home/hxy/abc.txt","wb");
    if (file == NULL)
    {
        printf("create file %s failure", filename);
        perror("create:");
        exit(-3);
    }
    //接收文件数据
    printf("recv begin\n");
    total = 0;
    while (1)
    {
        len = recv(sockfd, buf, sizeof(buf), 0);
        if (len == -1)
            break;
        total += len;
        //写入本地文件
        fwrite(buf, 1, len, file);
    }
    fclose(file);
    printf("recv file %s success total lenght %d\n", filename, total);
    //第六步:关闭 socket
    close(sockfd);
}