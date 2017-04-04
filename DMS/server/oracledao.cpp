//实现Oracle数据访问对象类
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
using namespace std;
#include "oracledao.h"
exec sql include sqlca;
exec sql begin declare section;
    sql_context g_context;//为了支持多线程
    char g_userpwd[30];
/**
 * create sequence dmslog_id;
 * create table dmslog(
 * id         number primary key,
 * logname    varchar2(32),
 * logip      varchar2(32),
 * pid        number,
 * logintime  date,
 * logouttime date,
 * durations  number);
 */
    struct DLogRec{
        char logname[32];
        char logip[32];
        int  pid;
        char logintime[52];
        char logouttime[52];
        int  durations;
    } g_log = {"","",0,"","",0};
exec sql end declare section;
OracleDao::OracleDao(const string& username,//数据库用户
              const string& password)//数据库口令
              throw (DBException){
    cout << "打开数据库开始..." << endl;
    sprintf(g_userpwd,"%s/%s",username.c_str(),password.c_str());
    exec sql enable threads;
    exec sql context allocate : g_context;
    exec sql context use : g_context;
    exec sql connect : g_userpwd;
    if(sqlca.sqlcode){
        ostringstream oss;
        oss << "ORA" << showpos /*为了把正负号打印出来*/ << sqlca.sqlcode;
        throw DBException(oss.str());
    }
    cout << "打开数据库完成..." << endl;
}
    //析构器,语法上析构函数也可以抛异常，但是一般不这么干，因为析构函数里面抛异常太
    //危险了，因为析构本身就是异常处理的一部分，如果你在异常过程当中，有析构函数被调用
    //而析构本身又抛出异常，这样可能会无限循环，最终进程会被系统杀死，所以析构函数
    //里最好不要抛异常，而且还要尽可能的吃掉所可能抛出的异常。
OracleDao::~OracleDao(){
    cout << "关闭数据库开始..." << endl;
    exec sql commit work release;

    cout << "关闭数据库完成..." << endl;
}
//插入
void OracleDao::insert(const MLogRec& log)throw(DBException){
    cout << "插入数据库开始..." << endl;
//    cout << log << endl;
    strcpy(g_log.logname,log.logname);
    strcpy(g_log.logip,log.logip);
    g_log.pid = log.pid;
    time_t t = log.logintime;
    tm* local = localtime(&t);
    sprintf(g_log.logintime,"%04d-%02d-%02d %02d:%02d:%02d",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday,
            local->tm_hour,
            local->tm_min,
            local->tm_sec);
    t = log.logouttime;
    local = localtime(&t);
    sprintf(g_log.logouttime,"%04d-%02d-%02d %02d:%02d:%02d",
            local->tm_year + 1900,
            local->tm_mon + 1,
            local->tm_mday,
            local->tm_hour,
            local->tm_min,
            local->tm_sec);
    g_log.durations = log.durations;
    exec sql insert into dmslog values(
                dmslog_id.nextval,
                :g_log.logname,
                :g_log.logip,
                :g_log.pid,
                to_date(:g_log.logintime,'yyyy-mm-dd hh24:mi:ss'),
                to_date(:g_log.logouttime,'yyyy-mm-dd hh24:mi:ss'),
                :g_log.durations);
    if(sqlca.sqlcode){
        ostringstream oss;
        oss << "ORA" << showpos /*为了把正负号打印出来*/ << sqlca.sqlcode;
        throw DBException(oss.str());
    }
    exec sql commit;
    cout << "插入数据库完成..." << endl;
}
#if 0
//将utf-8编码转换成gdk编码
zn@zn-OptiPlex-9010:~/demo/031117/DMS/server$ iconv -f utf-8 -t gdk oracledao.cpp > oracledao.pc
#endif
