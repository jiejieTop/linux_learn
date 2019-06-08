#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
pid_t child1, child2, child;
/*创建两个子进程*/
child1 = fork();
/*子进程 1 的出错处理*/
if (child1 == -1)
{
printf("Child1 fork error\n");
exit(1);
}
else if (child1 == 0) /*在子进程 1 中调用 execlp()函数*/
{
printf("In child1: execute 'ls -l'\n");
if (execlp("ls", "ls", "-l", NULL) < 0)
{
printf("Child1 execlp error\n");
}
}
else /*在父进程中再创建进程 2，然后等待两个子进程的退出*/
{
child2 = fork();
if (child2 == -1) /*子进程 2 的出错处理*/
{
printf("Child2 fork error\n");
exit(1);
}
else if(child2 == 0) /*在子进程 2 中使其暂停 5s*/
{
printf("In child2: sleep for 5 seconds and then exit\n");
sleep(5);
exit(0);
}
printf("In father process:\n");
child = waitpid(child1, NULL, 0); /* 阻塞式等待 */
if (child == child1)
{
printf("Get child1 exit code\n");
}
else
{
printf("Error occured!\n");
}
do
{
child = waitpid(child2, NULL, WNOHANG ); /* 非阻塞式等待 */
if (child == 0)
{
printf("The child2 process has not exited!\n");
sleep(1);
}
} while (child == 0);
if (child == child2)
{
printf("Get child2 exit code\n");
}
else
{
printf("Error occured!\n");
}
}
exit(0);
}