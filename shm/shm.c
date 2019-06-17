/** shm.c(share memory) */

/**
 * 共享内存是允许两个不相关的进程访问同一个逻辑内存的进程间通信方法，是在两个正在运行的进程之间共享和传递数据的一种非常有效的方式。
 * 
 * 共享内存的实现分为两个步骤，第一步是创建共享内存，这里用到的函数是 shmget()，也就是从内存中获得一段共享内存区域;
 * 第二步映射共享内存，也就是把这段创建的共享内存映射到具体的进程空间中，这里使用的函数是 shmat()。
 * 到这里，就可以使用这段共享内存了，也就是可以使用不带缓冲的 I/O 读写命令对其进行操作。
 * 除此之外，当然还有撤销映射的操作，其函数为 shmdt()。
 * 
 * 函数原型: int shmget(key_t key, int size, int shmflg)
 * 函数传入值:
 *  key：共享内存的键值，多个进程可以通过它访问同一个共享内存，其中有个特殊值 IPC_PRIVATE。它用于创建当前进程的私有共享内存
 *  size：共享内存区大小
 *  shmflg：同 open()函数的权限位，也可以用八进制表示法
 * 函数返回值:
 *  成功：共享内存段标识符
 *  出错： -1
 * 
 * 函数原型 char *shmat(int shmid, const void *shmaddr, int shmflg)
 * 函数传入值:
 *  shmid：要映射的共享内存区标识符
 *  shmaddr：将共享内存映射到指定地址（若为 0 则表示系统自动分配地址并把该段共享内存映射到调用进程的地址空间）
 *  shmflg:
 *    SHM_RDONLY：共享内存只读
 *    默认 0：共享内存可读写
 * 函数返回值
 *  成功：被映射的段地址
 *  出错： -1
 * 
 * 函数原型 int shmdt(const void *shmaddr)
 * 函数传入值: shmaddr：被映射的共享内存段地址
 * 函数返回值: 
 *  成功： 0
 *  出错： -1
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 2048
int main()
{
    pid_t pid;
    int shmid;
    char *shm_addr;
    char flag[] = "WROTE";
    char *buff;

    /* 创建共享内存 */
    if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    else
    {
        printf("Create shared-memory: %d\n",shmid);
    }

    /* 显示共享内存情况 */
    system("ipcs -m");

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    else if (pid == 0) /* 子进程处理 */
    {
        /*映射共享内存*/
        if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
        {
            perror("Child: shmat");
            exit(1);
        }

        else
        {
            printf("Child: Attach shared-memory: %p\n", shm_addr);
        }

        system("ipcs -m");
        /* 通过检查在共享内存的头部是否标志字符串"WROTE"来确认父进程已经向共享内存写入有效数据 */
        while (strncmp(shm_addr, flag, strlen(flag)))
        {
            printf("Child: Wait for enable data...\n");
            sleep(5);
        }

        /* 获取共享内存的有效数据并显示 */
        strcpy(buff, shm_addr + strlen(flag));
        printf("Child: Shared-memory :%s\n", buff);

        /* 解除共享内存映射 */
        if ((shmdt(shm_addr)) < 0)
        {
            perror("shmdt");
            exit(1);
        }
        else
        {
            printf("Child: Deattach shared-memory\n");
        }
        system("ipcs -m");
        /* 删除共享内存 */
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("Child: shmctl(IPC_RMID)\n");
            exit(1);
        }

        else
        {
            printf("Delete shared-memory\n");
        }

        system("ipcs -m");
    }
    
    else /* 父进程处理 */
    {
        /*映射共享内存*/
        if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
        {
            perror("Parent: shmat");
            exit(1);
        }

        else
        {
            printf("Parent: Attach shared-memory: %p\n", shm_addr);
        }

        sleep(1);
        printf("\nInput some string:\n");
        fgets(buff, BUFFER_SIZE, stdin);
        strncpy(shm_addr + strlen(flag), buff, strlen(buff));
        strncpy(shm_addr, flag, strlen(flag));

        /* 解除共享内存映射 */
        if ((shmdt(shm_addr)) < 0)
        {
            perror("Parent: shmdt");
            exit(1);
        }
        else
        {
            printf("Parent: Deattach shared-memory\n");
        }

        system("ipcs -m");
        waitpid(pid, NULL, 0);
        printf("Finished\n");
    }
    
    exit(0);
}