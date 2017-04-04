//声明客户线程类
#ifndef _CLIENTTHREAD_H
#define _CLIENTTHREAD_H
#include "logthread.h"
//客户线程类
//每个类各司其职，一个类最好就干一件事，
class ClientThread : public LogThread{
public:
    //构造器
    ClientThread(int connfd);//通信套接字
    //线程处理
    void run();
private:
    int m_connfd;//一个处于连接状态的通信套接字
};
#endif//_CLIENTTHREAD_H
