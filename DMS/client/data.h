//数据对象
#ifndef _DATA_H
#define _DATA_H
#include <unistd.h>
#include <iostream>
using namespace std;
//登入登出日志记录
struct LogRec{
    char logname[32];//登录名
    char logip[32];//登录IP
    pid_t pid;//登录进程ID
    long logtime;//登入登出时间
};
//匹配日志记录
//这里没有使用string类型的logname,logip,而是使用了字符数组。
//因为接下来我们会把整个数据块写到文件里。或者发到网上去，那么使用string就会
//比较麻烦，因为string的缓冲区是单独维护的。
//不能把一个string对象当成一个二进制块来操作。
//string里面存的只是一个指针，指向的内存在堆里面。堆跟对象放的不是一个地。
//用char数组的话，对象和char数组里放的数据是在一块的。不管写入文件还是发送到网上去
//操作起来会比较简单一点。
struct MLogRec{
    char logname[32];//登录名
    char logip[32];//登录IP
    pid_t pid;//登录进程ID
    long logintime;//登入时间
    long logouttime;//登出时间
    long durations;//登录时段
    friend ostream& operator<<(ostream& os,const MLogRec& log){
        return os << log.logname << ',' << log.logip << ','
                  << log.pid << ',' << log.logintime << ','
                  << log.logouttime << ',' << log.durations;
    }
};
#if 0
zn@zn-OptiPlex-9010:~/demo/031117/DMS/client$ g++ -c data.h
这样可以单独编译一个头文件，然后生成一个.gch的东西（预编译头）
zn@zn-OptiPlex-9010:~/demo/031117/DMS/client$ ls
client  data.h  data.h.gch  main.cpp  main.o  Makefile
#endif

#endif//_DATA_H
