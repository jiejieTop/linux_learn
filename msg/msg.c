/** msg.c */

/**
 * 消息队列就是一些消息的列表。用户可以从消息队列中添加消息和读取消息等。
 * 消息队列的实现包括创建或打开消息队列、添加消息、读取消息和控制消息队列这 4 种操作:
 * 其中创建或打开消息队列使用的函数是 msgget()，这里创建的消息队列的数量会受到系统消息队列数量的限制；
 * 添加消息使用的函数是 msgsnd()函数，它把消息添加到已打开的消息队列末尾；
 * 读取消息使用的函数是msgrcv()，它把消息从消息队列中取走，与 FIFO 不同的是，这里可以指定取走某一条消息；
 * 最后控制消息队列使用的函数是 msgctl()，它可以完成多项功能。
 * 
 */