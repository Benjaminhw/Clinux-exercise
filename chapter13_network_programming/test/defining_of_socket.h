struct sockaddr
{
    unsigned short sa_family;
    /*地址族*/
    char sa_data[14];
    /*14 字节的协议地址，包含该 socket 的 IP 地址和端口号。*/
};
struct sockaddr_in
{
    short int sin_family;
    /*地址族*/
    unsigned short int sin_port; /*端口号*/
    struct in_addr sin_addr;
    /*IP 地址*/
    unsigned char sin_zero[8]; /*填充 0 以保持与 struct sockaddr 同样大小*/
};
typedef uint32_t in_addr_t;
struct in_addr
{
    in_addr_t s_addr;
};

//函数原型：
#include <netdb.h>
struct hostent *gethostbyname(const char *hostname);
struct hostent *gethostbyaddr(const char *addr, size_t len, int family);
//结构体：
struct hostent
{
    char *h_name;       /*正式主机名*/
    char **h_aliases;   /*主机别名*/
    int h_addrtype;     /*主机 IP 地址类型 IPv4 为 AF_INET*/
    int h_length;       /*主机 IP 地址字节长度，对于 IPv4 是 4 字节，即 32 位*/
    char **h_addr_list; /*主机的 IP 地址列表*/
}
#define h_addr h_addr_list[0] /*保存的是 ip 地址*/