/** signal.c */

/**
 * 一个进程可以决定在该进程中需要对哪些信号进行什么样的处理。例如，一个进程可以选择忽略某些信号而只处理其他一些信号，
 * 另外，一个进程还可以选择如何处理信号。总之，这些都是与特定的进程相联系的。因此，首先就要建立进程与其信号之间的对
 * 应关系，这就是信号的处理。
 * 
 * 如果进程要处理某一信号，那么就要在进程中安装该信号。安装信号主要用来确定信号值及进程针对该信号值的动作之间的映射关系，
 * 即进程将要处理哪个信号；该信号被传递给进程时，将执行何种操作。
 * 
 * linux主要有两个函数实现信号的安装：signal()、sigaction()。其中signal()在可靠信号系统调用的基础上实现, 是库函数。
 * 它只有两个参数，不支持信号传递信息，主要是用于前32种非实时信号的安装；
 * 而sigaction()是较新的函数（由两个系统调用实现：sys_signal以及sys_rt_sigaction），有三个参数，支持信号传递信息，主要用来与 
 * sigqueue() 系统调用配合使用，当然，sigaction()同样支持非实时信号的安装。sigaction()优于signal()主要体现在支持信号带有参数。
 * 
 * 常见信号的含义及其默认操作：
 * 信 号 名                     含 义                               默 认 操 作
 * 
 * SIGHUP       该信号在用户终端连接（正常或非正常）结束时发出，              终止
 *              通常是在终端的控 制进程结束时，通知同一会话内的      
 *              各个作业与控制终端不再关联 
 * 
 * SIGINT       该信号在用户键入 INTR 字符（通常是 Ctrl-C）时发出，         终止
 *              终端驱动程序发送此信号并送到前台进程中的每一个进程            
 * 
 * SIGQUIT      该信号和 SIGINT 类似，                                  终止
 *              但由 QUIT 字符（通常是 Ctrl-\）来控制                     
 * 
 * SIGILL       该信号在一个进程企图执行一条非法指令时（可执行文件本          终止
 *              身出现错误，或者试图执行数据段、堆栈溢出时）发出 
 * 
 * SIGFPE       该信号在发生致命的算术运算错误时发出。这里不仅包括浮点        终止  
 *              运算错误，还包括溢出及除数为 0 等其他所有的算术错误         
 * 
 * SIGKILL      该信号用来立即结束程序的运行，                            终止
 *              并且不能被阻塞、处理或忽略
 * 
 * SIGALRM      该信号当一个定时器到时的时候发出                          终止
 * 
 * SIGSTOP      该信号用于暂停一个进程，且不能被阻塞、处理或忽略            暂停进程
 * 
 * SIGTSTP      该信号用于交互停止进程，用户键入 SUSP 字符时              停止进程
 *              （通常是 Ctrl+Z）发出这个信号                       
 * 
 * SIGCHLD      子进程改变状态时，父进程会收到这个信号                     忽略
 * 
 * SIGABORT      进程异常终止时发出
 */

/**
 * 函数原型: void (*signal(int signum, void (*handler))(int)))(int); 
 * 如果该函数原型不容易理解的话，可以参考下面的分解方式来理解： 
 * typedef void (*sighandler_t)(int)； 
 * sighandler_t signal(int signum, sighandler_t handler)); 
 * 
 * signum：指定信号代码
 * handler：
 *   SIG_IGN：忽略该信号
 *   SIG_DFL：采用系统默认方式处理信号
 *   自定义的信号处理函数指针
 * 
 * retern:
 *   成功：以前的信号处理配置
 *   出错：-1
 * 
 */

/** 
 * 函数原型: int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
 * 
 * signum：信号代码，可以为除 SIGKILL 及 SIGSTOP 外的任何一个特定有效的信号
 * act：指向结构 sigaction 的一个实例的指针，指定对特定信号的处理
 * oldact：保存原来对相应信号的处理
 * 
 * retern:
 *   成功：以前的信号处理配置
 *   出错：-1
 * 
*/



