/* socket_basics.c */

/**
 * socket 编程的基本函数有 socket()、 bind()、 listen()、 accept()、 read()、write()、send()、 sendto()、 recv()以及 recvfrom()、recvmsg()、sendmsg()等:
 *  socket()： 该函数用于建立一个 socket 连接， 可指定 socket 类型等信息。 在建立了 socket 连接之后，可对 sockaddr 或 sockaddr_in 结构进行初始化，以保存所建立的 socket 地址信息。
 *  bind()：该函数是用于将本地 IP 地址绑定到端口号，若绑定其他 IP 地址则不能成功。另外，它主要用于 TCP 的连接，而在 UDP 的连接中则无必要。
 *  listen()：在服务端程序成功建立套接字和与地址进行绑定之后，还需要准备在该套接字上接收新的连接请求。此时调用 listen()函数来创建一个等待队列，在其中存放未处理的客户端连接请求。
 *  accept()：服务端程序调用 listen()函数创建等待队列之后，调用 accept()函数等待并接收客户端的连接请求。它通常从由 bind()所创建的等待队列中取出第一个未处理的连接请求。
 *  connect()：该函数在 TCP 中是用于 bind()的之后的 client 端，用于与服务器端建立连接，而在 UDP中由于没有了 bind()函数，因此用 connect()有点类似 bind()函数的作用。
 *  send()和 recv()：这两个函数分别用于发送和接收数据，可以用在 TCP 中，也可以用在 UDP 中。当用在 UDP 时，可以在 connect()函数建立连接之后再用。
 *  sendto()和 recvfrom()： 这两个函数的作用与 send()和 recv()函数类似， 也可以用在 TCP 和 UDP 中。当用在 TCP 时，后面的几个与地址有关参数不起作用，
 *   函数作用等同于 send()和 recv()；当用在UDP 时，可以用在之前没有使用 connect()的情况下，这两个函数可以自动寻找指定地址并进行连接。
 * 
 * tcp协议流程：
 *  服务器：socket()->bind()->listen()->accept()->read()/write()->close()
 *  客户端：socket()->connect()->read()/write()->close()
 * 
 * udp协议流程：
 * socket()->bind()->recvfrom()/sendto()/send()->close()
 * 
 * 函数原型:int socket(int domain,int type, int protocol)
 * family：协议族
 *   AF_INET： IPv4 协议
 *   AF_INET6： IPv6 协议
 *   AF_LOCAL： UNIX 域协议
 *   AF_ROUTE：路由套接字（socket）
 *   AF_KEY：密钥套接字（socket）
 * type：套接字类型
 *   SOCK_STREAM：字节流套接字 socket
 *   SOCK_DGRAM：数据报套接字 socket
 *   SOCK_RAW：原始套接字 socket
 * protocol：相应的传输协议，一般取为0
 * 函数返回值
 *  成功：非负套接字描述符。
 *  出错： -1
 * 
 * 函数原型 int bind(int sockfd, struct sockaddr *my_addr, int addrlen)
 * 函数传入值
 * socktd：套接字描述符
 * my_addr：本地地址
 * addrlen：地址长度
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 函数原型 int listen(int sockfd, int backlog)
 * 函数传入值
 * socktd：套接字描述符
 * backlog：请求队列中允许的最大请求数，大多数系统缺省值为 5
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 函数原型 int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
 * 函数传入值
 * socktd：套接字描述符
 * addr：客户端地址
 * addrlen：地址长度
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 函数原型 int connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
 * 函数传入值
 * socktd：套接字描述符
 * serv_addr：服务器端地址
 * addrlen：地址长度
 * 函数返回值
 *  成功： 0
 *  出错： -1
 * 
 * 函数原型 int send(int sockfd, const void *msg, int len, int flags)
 * 函数传入值
 * socktd：套接字描述符
 * msg：指向要发送数据的指针
 * len：数据长度
 * flags：一般为 0
 * 函数返回值
 *  成功：发送的字节数
 *  出错： -1
 * 
 * 函数原型 int recv(int sockfd, void *buf,int len, unsigned int flags)
 * 函数传入值
 * socktd：套接字描述符
 * buf：存放接收数据的缓冲区
 * len：数据长度
 * flags：一般为 0
 * 函数返回值
 *  成功：接收的字节数
 *  出错： -1
 * 
 * 函数原型 int sendto(int sockfd, const void *msg,int len, unsigned int flags, const struct sockaddr *to, int tolen)
 * 函数传入值
 * socktd：套接字描述符
 * msg：指向要发送数据的指针
 * len：数据长度
 * flags：一般为 0
 * to：目地机的 IP 地址和端口号信息
 * tolen：地址长度
 * 函数返回值
 *  成功：发送的字节数
 *  出错： -1
 * 
 * 函数原型 int recvfrom(int sockfd,void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen)
 * 函数传入值
 * socktd：套接字描述符
 * buf：存放接收数据的缓冲区
 * len：数据长度
 * flags：一般为 0
 * from：源主机的 IP 地址和端口号信息
 * tolen：地址长度
 * 函数返回值
 *  成功：接收的字节数
 *  出错： -1
 * 
 */




