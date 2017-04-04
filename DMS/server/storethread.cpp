//实现存储线程类
#include <iostream>
using namespace std;
#include "storethread.h"
#include "logqueue.h"
//存储线程类
StoreThread::StoreThread(LogDao& dao)//数据访问对象
    :m_dao(dao)
{

}
//线程处理
void StoreThread::run(){
    MLogRec log;
    for(;;){
        //每弹出一条日志记录
        g_logQueue >> log;
        //插入数据库
        try{
            m_dao.insert(log);
        }
        catch(DBException& ex){
            cout << ex.what() << endl;
        }
    }
}
