//数据访问对象接口类dao(data access object)
#ifndef _LOGDAO_H
#define _LOGDAO_H
#include "except.h"
#include "data.h"
//数据访问对象接口类
class LogDao{
public:
    //通过指向子类对象的基类指针去析构的时候，基类的析构函数必须是虚函数
    //不然它只会调用基类的析构，不调用子类的析构
    //这里写一个空的析构函数，只是为了要virtual,这就是所谓的空虚析构
    virtual ~LogDao(){}//系统提供的默认析构函数不是virtual的
    //插入
    virtual void insert(const MLogRec& log)throw(DBException) = 0;
};
#endif//_LOGDAO_H
