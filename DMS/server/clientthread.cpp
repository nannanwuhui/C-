//实现客户线程类
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#include "clientthread.h"
#include "logqueue.h"
//构造器
ClientThread::ClientThread(int connfd)//通信套接字
    :m_connfd(connfd)
{

}
//线程处理 一般情况下，对象谁创建，谁销毁，但是ServerSocket没机会销毁ClientThread对象
//更准确的来讲应该是谁知道它什么时候该销毁，谁销毁
void ClientThread::run(){
    unsigned long long logs;
    MLogRec log;
    //0表示使用同步模式
    for(logs = 0;;++logs){
        //如果客户端把socket给close了，服务端还在接收，就会返回0
        //可能存在recv收到了比如sizeof(log)/2个字节，剩下的还在路上,而recv返回了
        //下一次调用recv的时候收到了，这样的话，数据就会发生错乱。
        //内核缓冲区可能只收到了不到sizeof(log)个字节
        ssize_t rlen;
        for(size_t len = sizeof(log);len;len -= rlen){
            if((rlen = recv(m_connfd,(char*)&log/*保证以字节为单位来计算偏移量*/ + (sizeof(log) - len),len,0)) <= 0){// -1（出错）
                goto escape;//这里可以使用break么？
            }
        }
        //网络字节序转主机字节序
        log.pid = ntohl(log.pid);
        log.logintime = ntohl(log.logintime);
        log.logouttime = ntohl(log.logouttime);
        log.durations = ntohl(log.durations);
        g_logQueue << log;
    }
    escape:
    cout << "接收到" << logs << "条匹配日志记录。" << endl;
    close(m_connfd);
    //线程过程函数一返回，线程也就结束了
    delete this;//线程结束，销毁客户线程对象
}
