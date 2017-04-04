//声明文件数据访问对象类
#ifndef _FILEDAO_H
#define _FILEDAO_H
#include <fstream>
using namespace std;
#include "logdao.h"
//文件数据访问对象类
class FileDao : public LogDao{
public:
    //构造器,可以抛异常，有的时候构造函数还必须要抛异常，因为构造函数没有返回值
    FileDao(const string& path) throw (DBException);//文件路径
    //析构器,语法上析构函数也可以抛异常，但是一般不这么干，因为析构函数里面抛异常太
    //危险了，因为析构本身就是异常处理的一部分，如果你在异常过程当中，有析构函数被调用
    //而析构本身又抛出异常，这样可能会无限循环，最终进程会被系统杀死，所以析构函数
    //里最好不要抛异常，而且还要尽可能的吃掉所可能抛出的异常。
    ~FileDao();
    //插入
    void insert(const MLogRec& log)throw(DBException);
private:
    ofstream m_ofs;//输出文件流
};
#endif//_FILEDAO_H
