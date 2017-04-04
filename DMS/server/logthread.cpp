//实现线程类
#include <pthread.h>
#include <iostream>
using namespace std;
#include "logthread.h"

//启动线程
void LogThread::start()throw(ThreadException){
    cout << "启动线程开始..." << endl;
    pthread_t tid;
    if(pthread_create(&tid,NULL,run,this))
        throw ThreadException("启动线程失败");
    cout << "启动线程完成..." << endl;
}
//线程过程
void* LogThread::run(void* arg){
    //客户机停止上传的时候，客户机线程自动结束，存储线程一直在运行，直到进程结束
    //所以这些线程都不需要汇合，也就是说不需要主线程来回收资源
    pthread_detach(pthread_self());//线程不可汇合，资源自动释放
    static_cast<LogThread*>(arg)->run();
    return NULL;
}
