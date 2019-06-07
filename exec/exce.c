/** exec 函数族 */

/**
 * exec 函数族就提供了一个在进程中启动另一个程序执行的方法。它可以根据指定的文件名或
 * 目录名找到可执行文件，并用它来取代原调用进程的数据段、代码段和堆栈段，在执行完之后，原调用进
 * 程的内容除了进程号外，其他全部被新的进程替换了。另外，这里的可执行文件既可以是二进制文件，也
 * 可以是 Linux 下任何可执行的脚本文件。
 * 
 * 在 Linux 中使用 exec 函数族主要有两种情况。
 *    当进程认为自己不能再为系统和用户做出任何贡献时， 就可以调用 exec 函数族中的任意一个函数让自己重生。
 *    如果一个进程想执行另一个程序，那么它就可以调用 fork()函数新建一个进程，然后调用 exec 函
 *     数族中的任意一个函数，这样看起来就像通过执行应用程序而产生了一个新进程（这种情况非常普遍）。 
 * 
 */

/**
 * ************************** exec 函数族成员函数语法 *****************************
 * 所需头文件 #include <unistd.h>
 * 函数原型
 * int execl(const char *path, const char *arg, ...)
 * int execv(const char *path, char *const argv[])
 * int execle(const char *path, const char *arg, ..., char *const envp[])
 * int execve(const char *path, char *const argv[], char *const envp[])
 * int execlp(const char *file, const char *arg, ...)
 * int execvp(const char *file, char *const argv[])
 * 函数返回值 -1：出错 
 */




int main(void)
{


    return 0;
}
