/** network_basics.c */

/**
 * 下面首先介绍两个重要的数据类型： sockaddr 和 sockaddr_in， 这两个结构类型都是用来保存 socket 信息的，如下所示：
    struct sockaddr
    {
        unsigned short sa_family;   // 协议族
        char sa_data[14];           // 14 字节的协议地址，包含该socket 的IP 地址和端口号。       
    };

    struct sockaddr_in
    {
        short int sa_family; 
        unsigned short int sin_port; // 端口号
        struct in_addr sin_addr; //IP 地址
        unsigned char sin_zero[8]; //填充 0 以保持与 struct sockaddr 同样大小
    };
 * 
 * sa_family 字段可选的常见值:
 *  AF_INET： IPv4 协议
 *  AF_INET6： IPv6 协议
 *  AF_LOCAL： UNIX 域协议
 *  AF_LINK：链路地址协议
 *  AF_KEY：密钥套接字（socket）
 * 
 * 
 * 网络字节序：
 * 计算机数据存储有两种字节优先顺序：高位字节优先（称为大端模式）和低位字节优先（称为小端模式，PC 机通常采用小端模式）。
 *  Internet 上数据以高位字节优先顺序在网络上传输，因此在有些情况下，需要对这两个字节存储优先顺序进行相互转化。
 * 这里用到了 4 个函数： htons()、 ntohs()、 htonl()和 ntohl()。这 4 个地址分别实现网络字节序和主机字节序的转化，
 * 这里的 h 代表 host， n 代表 network， s 代表 short， l 代表 long。通常 16 位的 IP 端口号用 s 代表，而 IP 地址用 l 来代表。
 * 
 * uint16_t htons(unit16_t host16bit)
 * uint32_t htonl(unit32_t host32bit)
 * uint16_t ntohs(unit16_t net16bit)
 * uint32_t ntohs(unit32_t net32bit)
 * 
 * 函数传入值 host16bit：
 *  主机字节序的 16 位数据
 *  host32bit：主机字节序的 32 位数据
 *  net16bit：网络字节序的 16 位数据
 *  net32bit：网络字节序的 32 位数据
 * 函数返回值
 *  成功：返回要转换的字节序
 *  出错： -1
 * 
 * 地址格式转化：
 * inet_pton()函数是将点分十进制地址映射为二进制地址， 而 inet_ntop()是将二进制地址映射为点分十进制地址
 * 函数原型 int inet_pton(int family, const char *strptr, void *addrptr)
 * 函数传入值
 * family：
 *  AF_INET： IPv4 协议
 *  AF_INET6： IPv6 协议
 * strptr：要转化的值
 * addrptr：转化后的地址
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 函数原型 int inet_ntop(int family, void *addrptr, char *strptr, size_t len)
 * 函数传入值 
 * family：
 *  AF_INET： IPv4 协议
 *  AF_INET6： IPv6 协议
 * 函数传入值
 * addrptr：转化后的地址
 * strptr：要转化的值
 * len：转化后值的大小
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 主机名和地址的转化，最为常见的有 gethostbyname()、 gethostbyaddr()和 getaddrinfo()等，
 * 其中 gethostbyname()是将主机名转化为 IP 地址，gethostbyaddr()则是逆操作， 是将 IP 地址转化为主机名， 
 * 另外 getaddrinfo()还能实现自动识别 IPv4 地址和 IPv6地址
 * 
 * gethostbyname()和 gethostbyaddr()都涉及一个 hostent 的结构体，如下所示：
    struct hostent
    {
        char *h_name;       // 正式主机名
        char **h_aliases;   // 主机别名
        int h_addrtype; // 地址类型
        int h_length;// 地址字节长度
        char **h_addr_list;//指向 IPv4 或 IPv6 的地址指针数组
    }

 * 调用 gethostbyname()函数或 gethostbyaddr()函数后就能返回 hostent 结构体的相关信息。getaddrinfo()函数涉及一个 addrinfo 的结构体，如下所示：
    struct addrinfo
    {
        int ai_flags;       //  AI_PASSIVE, AI_CANONNAME;
        int ai_family;      //地址族
        int ai_socktype;    //socket 类型
        int ai_protocol;    //协议类型
        size_t ai_addrlen;  //地址字节长度
        char *ai_canonname; //主机名
        struct sockaddr *ai_addr;   //socket 结构体
        struct addrinfo *ai_next;   //下一个指针链表
    }
 * 
 * 函数原型 struct hostent *gethostbyname(const char *hostname)
 * 函数原型 int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints,struct addrinfo **result)
 * node：网络地址或者网络主机名
 * service：服务名或十进制的端口号字符串
 * hints：服务线索
 * result：返回结果
 * 
 * 在调用之前，首先要对 hints 服务线索进行设置。它是一个 addrinfo 结构体
 * ai_flags
 *   AI_PASSIVE：该套接口是用作被动地打开
 *   AI_CANONNAME：通知 getaddrinfo 函数返回主机的名字
 * ai_family
 *   AF_INET： IPv4 协议
 *   AF_INET6： IPv6 协议
 *   AF_UNSPEC： IPv4 或 IPv6 均可
 * ai_socktype 
 *   SOCK_STREAM：字节流套接字 socket（TCP）
 *   SOCK_DGRAM：数据报套接字 socket（UDP）
 * ai_protocol
 *   IPPROTO_IP： IP 协议
 *   IPPROTO_IPV4： IPv4 协议 4 IPv4
 *   IPPROTO_IPV6： IPv6 协议
 *   IPPROTO_UDP： UDP
 *   IPPROTO_TCP： TCP
 * 
 * 提示：
 * （ 1）通常服务器端在调用 getaddrinfo()之前， ai_flags 设置 AI_PASSIVE，用于 bind()函数，主机名 nodename 通常会设置为 NULL。
 * （ 2）客户端调用 getaddrinfo()时， ai_flags 一般不设置 AI_PASSIVE，但是主机名nodename 和服务名 servname（端口）则应该不为空。
 * （ 3） 即使不设置 ai_flags 为 AI_PASSIVE，取出的地址也可以被绑定，很多程序中ai_flags 直接设置为 0，即 3 个标志位都不设置，
 * 这种情况下只要 hostname 和 servname设置的没有问题就可以正确绑定。
 * 
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
    struct addrinfo hints, *res = NULL;
    int rc;

    memset(&hints, 0, sizeof(hints));

    /*设置 addrinfo 结构体中各参数 */
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    /*调用 getaddinfo 函数*/
    rc = getaddrinfo("localhost", NULL, &hints, &res);
    if (rc != 0)
    {
        perror("getaddrinfo");
        exit(1);
    }

    else
    {
        printf("Host name is %s\n", res->ai_canonname);
    }

    exit(0);
}






