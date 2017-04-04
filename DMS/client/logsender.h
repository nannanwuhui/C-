//日志发送器接口类
#ifndef _LOGSENDER_H
#define _LOGSENDER_H
#include <list>
using namespace std;
#include "data.h"
#include "except.h"
/**
 * @brief The LogSender class
 * 既然它是一个用于实现多态的抽象基类
 * 那么应该允许用户以指向子类的基类指针的形式来释放子类对象
 * 为了防止子类部分不能被正确的析构，所以要把析构函数定义成虚函数
 */
class LogSender{
public:
    //不管用户会不会这样去用，既然有了多态性，就没有理由不把你的析构函数
    //定义成虚的，万一用户要这样用，delete一个指向子类对象的基类指针
    virtual ~LogSender(){}//保证子类的析构函数可以被调用到
    //发送日志
    virtual void sendLog(list<MLogRec>& logs) throw (SendException) = 0;
};
#endif //_LOGSENDER_H
