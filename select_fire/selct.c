#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/**函数原型:
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

int main(void)
{



    return 0;
}

