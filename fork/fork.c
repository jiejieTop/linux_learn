/* fork.c */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    pid_t result;
    /*调用 fork()函数*/
    result = fork();
    /*通过 result 的值来判断 fork()函数的返回情况，首先进行出错处理*/
    if(result == -1)
    {
        printf("Fork error\n");
    }
    else if (result == 0) /*返回值为 0 代表子进程*/
    {
        printf("The returned value is %d\nIn child process!!\nMy PID is %d\n\n",result,getpid());

    }
    else /*返回值大于 0 代表父进程*/
    {
        printf("The returned value is %d\nIn father process!!\nMy PID is %d\n\n",result,getpid());
    }
    return result;
}
