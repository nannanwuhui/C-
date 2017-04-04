//实现日志队列类
#include <iostream>
using namespace std;
#include "logqueue.h"
LogQueue g_logQueue;//进程一启动就会创建，先于其他对象(ClientThread,StoreThread)
//构造器
LogQueue::LogQueue(){
    //创建同步互斥量，分配内核资源
    pthread_mutex_init(&m_mutex,0);
    //创建同步条件变量
    pthread_cond_init(&m_cond,0);
}
//析构器
LogQueue::~LogQueue(){
    //销毁同步条件变量
    pthread_cond_destroy(&m_cond);
    //销毁同步互斥量
    pthread_mutex_destroy(&m_mutex);
}
//压入日志记录
LogQueue& LogQueue::operator<< (const MLogRec& log){
    cout << "压入日志记录开始..." << endl;
    pthread_mutex_lock(&m_mutex);
    m_logs.push_back(log);
    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
    cout << "压入日志记录完成..." << endl;
    return *this;
}
//弹出日志记录
LogQueue& LogQueue::operator>> (MLogRec& log){
    cout << "弹出日志记录开始..." << endl;
    pthread_mutex_lock(&m_mutex);
    //多个消费者的时候，可能发生竞争，一个获得了锁，另一个执行m_log.front()就
    //可能会失败，所以要在睡醒以后再次判断m_logs.empty();
    while(m_logs.empty()){
        cout << "等待日志记录..." << endl;
        pthread_cond_wait(&m_cond,&m_mutex);
    }
    log = m_logs.front();
    m_logs.pop_front();
    pthread_mutex_unlock(&m_mutex);
    cout << "弹出日志记录完成..." << endl;
    return *this;
}

