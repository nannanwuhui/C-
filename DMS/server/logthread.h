//声明线程类
#ifndef _LOGTHREAD_H
#define _LOGTHREAD_H
#include "except.h"
//线程类
class LogThread{
public:
    virtual ~LogThread(){}
    //启动线程
    void start()throw(ThreadException);
    //线程处理函数
    virtual void run() = 0;
private:
    //线程过程
    static void* run(void* arg);
};
#endif//_LOGTHREAD_H
