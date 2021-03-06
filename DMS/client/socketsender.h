//声明网络日志发送器接口类
#ifndef _SOCKETSENDER_H
#define _SOCKETSENDER_H
#include "logsender.h"
#include "workthread.h"
//网络日志发送器类
class SocketSender : public LogSender{
public:
    //构造器
    SocketSender(const string& ip,      //服务器IP地址
                 short port,            //服务器端口号
                 const string& failFile,//发送失败文件
                 WorkThread* work = NULL);
    //发送日志 可以throw(ClientException)
    //加上throw(SendException),异常就会被自己捕获，而不是被系统捕获
    void sendLog(list<MLogRec>& logs) throw (SendException);
private:
    //连接服务器
    void connectServer() throw (SocketException);
    //读取发送失败文件
    void readFailFile(list<MLogRec>& logs) throw (ReadException);
    //发送数据
    void sendData(list<MLogRec>& logs) throw (SendException);
    //保存发送失败文件
    void saveFailFile(list<MLogRec>& logs) throw (SaveException);
    string m_ip;        //服务器ip地址
    short  m_port;      //服务器端口号
    string m_failFile;  //发送失败文件
    int    m_sockfd;    //套接字描述符
    WorkThread* m_work; //工作线程对象
};
#endif //_SOCKETSENDER_H
