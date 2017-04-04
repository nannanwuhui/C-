//异常类
#ifndef _EXCEPT_H
#define _EXCEPT_H
#include <string>
using namespace std;
//服务器异常
class ServerException:public exception{
public:
    ServerException(void):m_msg("服务器异常!"){}
    ServerException(const string& msg):m_msg("服务器异常:"){
       m_msg += msg;
       m_msg += "!";
    }
    /**
      * 因为我们是从exception基类里继承的，在exception基类里面，它把自己
      * 的析构函数定义成了虚函数，而且不抛出任何异常，那么从我的这个类的实现角度来讲，
      * 我是可以不加析构函数的，因为我没有分配任何资源，但如果你不写析构函数，那么系统
      * 就会给你一个缺省的析构函数，缺省的析构函数是没有空异常说明的，也就是说可以
      * 抛出任何类型的异常。这样就会比基类抛出更多的异常。不能形成有效的覆盖。
      * 多态形成有效覆盖有几个前提：其中有一个是覆盖版本不能比基类版本声明更多的异常
      * 所以为了表示子类的析构能够以多态的方式来体现，所以必须强调它不比基类抛出更多
      * 的异常
      */
    ~ServerException()throw(){}//不抛出任何异常
    //覆盖基类里的what函数
    const char* what() const throw (){
        return m_msg.c_str();
    }
private:
    string m_msg;
};
//数据库异常
class DBException:public ServerException{
public:
    DBException():ServerException("备份错误"){}
    DBException(const string& msg):ServerException(msg){}
};
//网络异常
class SocketException:public ServerException{
public:
    SocketException():ServerException("网络错误"){}
    SocketException(const string& msg):ServerException(msg){}
};
//线程异常
class ThreadException:public ServerException{
public:
    ThreadException():ServerException("发送错误"){}
    ThreadException(const string& msg):ServerException(msg){}
};
#endif//_EXCEPT_H
