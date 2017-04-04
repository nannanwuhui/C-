//实现网络日志发送器接口类
#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "socketsender.h"
//网络日志发送器类
SocketSender::SocketSender(const string& ip,short port,
                           const string& failFile,
                           WorkThread* work /*= NULL*/)
    :m_ip(ip),
     m_port(port),
     m_failFile(failFile),
     m_work(work)
{

}
/**
  * logs不是SocketSender的成员变量，而是reader的成员变量，作为引用传进来的，
  * 既然是引用，就不用做复制，这样始终就只有一个容器。不用引用的话，从功能上来讲，
  * 肯定也是对的，但是要做一次大的拷贝，效率会低一点。
  * 虽然这个成员变量在reader中是作为私有成员来定义的，但是我们却在另外一个类
  * 里直接去访问了它的私有成员，我们是借助于readLog把reader的私有成员的一个引用给
  * 返回出来了。这样既不用用友元，也不用改变sendLog的公有属性，但一样可以访问
  * reader的私有成员，这是建立在可信赖的公有接口基础之上的，这样我们并不认为会
  * 对封装性造成破坏。这是一种有限的公开，不是任意的公开，从设计层面上来讲是合理的
  */
    //发送日志
void SocketSender::sendLog(list<MLogRec>& logs) throw (SendException){
    cout << "发送日志开始..." << endl;
    try{
        try{
            //传进去的参数是这次匹配好的，我要和之前发送失败的混合起来一块发
            //读取发送失败文件
            readFailFile(logs);
        }
        catch(ReadException& ex){
            cout << "无发送失败文件!" << endl;
        }
        //连接服务器
        connectServer();
        //发送数据
        sendData(logs);
    }
    catch(SocketException& ex){
        //保存发送失败文件
        saveFailFile(logs);
        throw SendException("连接错误");
    }
    catch(SendException& ex){
        //保存发送失败文件
        saveFailFile(logs);
        throw SendException("发送错误");
    }
    cout << "发送日志完成。" << endl;
}
    //连接服务器
void SocketSender::connectServer() throw (SocketException){
    cout << "连接服务器开始..." << endl;
    if((m_sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
        throw SocketException();
    }
    //in(internet的意思，互联网的地址结构) sockaddr_un(unix本地的地址结构)
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);//主机字节序转网络字节序
    addr.sin_addr.s_addr = inet_addr(m_ip.c_str());//字符串转32位无符号整数（网络字节序）
    if(connect(m_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1){
        close(m_sockfd);
        throw SocketException(strerror(errno));
    }
    cout << "连接服务器完成。" << endl;
}
    //读取发送失败文件
void SocketSender::readFailFile(list<MLogRec>& logs) throw (ReadException){
    cout << "读取发送失败文件开始..." << endl;
    ifstream ifs(m_failFile.c_str(),ios::binary);
    if(!ifs)
        throw ReadException();
    MLogRec log;
    while(ifs.read((char*)&log,sizeof(log))){
        logs.push_front(log);
    }
    if(!ifs.eof()){
        throw ReadException();
    }
    ifs.close();
    unlink(m_failFile.c_str());
    cout << "读取发送失败文件完成。" << endl;
}
    //发送数据
void SocketSender::sendData(list<MLogRec>& logs) throw (SendException){
    cout << "发送数据开始..." << endl;
    while(!logs.empty()){
        MLogRec log = logs.front();
        log.pid = htonl(log.pid);
        log.logintime = htonl(log.logintime);
        log.logouttime = htonl(log.logouttime);
        log.durations = htonl(log.durations);
        if(send(m_sockfd,&log,sizeof(log),0) == -1){
            close(m_sockfd);
            throw SendException();
        }
        //若有工作线程对象(GUI)
        if(m_work){
            ostringstream oss;
            oss << logs.front();
            m_work->update(oss.str());//更新界面
        }
        //删除发送成功的匹配日志记录，剩下的存入发送失败文件
        logs.pop_front();
    }
    close(m_sockfd);
    cout << "发送数据完成。" << endl;
}
    //保存发送失败文件
void SocketSender::saveFailFile(list<MLogRec>& logs) throw (SaveException){
    cout << "保存发送失败文件开始..." << endl;
    if(!logs.empty()){
        ofstream ofs(m_failFile.c_str(),ios::binary);
        if(!ofs){
            throw SaveException();
        }
        while(!logs.empty()){
            ofs.write((char*)&logs.front(),sizeof(MLogRec));
            logs.pop_front();
        }
        ofs.close();
    }
    cout << "保存发送失败文件完成。" << endl;
}
