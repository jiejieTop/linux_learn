#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * 函数原型:
 * int select(int numfds, fd_set *readfds, fd_set *writefds，
 *            fd_set *exeptfds, struct timeval *timeout) 
 * numfds：该参数值为需要监视的文件描述符的最大值加 1
 * readfds：由 select()监视的读文件描述符集合
 * writefds：由 select()监视的写文件描述符集合
 * exeptfds：由 select()监视的异常处理文件描述符集合
 * timeout 取值有3种：
 *      NULL：永远等待，直到捕捉到信号或文件描述符已准备好为止
 *      具体的等待时间值： struct timeval 类型的指针，若等待了 timeout 时间还没有检测到任何文件描符准备好，就立即返回
 *      0：从不等待，测试所有指定的描述符并立即返回
 * return : 大于 0：成功，返回准备好的文件描述符的数目
 *          0：超时
 *          -1：出错
 */

/********************* select()文件描述符处理函数 *****************************
 * 
 * FD_ZERO(fd_set *set)             清除一个文件描述符集
 * FD_SET(int fd, fd_set *set)      将一个文件描述符加入文件描述符集中
 * FD_CLR(int fd, fd_set *set)      将一个文件描述符从文件描述符集中清除
 * FD_ISSET(int fd, fd_set *set)    如果文件描述符 fd 为 fd_set 集中的一个元素，则返回非零值，
 * 可以用于调用 select()之后测试文件描述符集中的文件描述符是否有变化 
 * 
 * 一般来说，在使用 select()函数之前，首先使用 FD_ZERO()和 FD_SET()来初始化文件描述符集，在使用了
 * select()函数时，可循环使用 FD_ISSET()来测试描述符集，在执行完对相关文件描述符的操作之后，使用
 * FD_CLR()来清除描述符集。 
 */

int main(void)
{



    return 0;
}

