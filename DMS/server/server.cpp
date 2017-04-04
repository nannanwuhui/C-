//实现服务器类
#include "server.h"
//构造器
//类类型的成员只能在初始化表里进行初始化
Server::Server(LogDao& dao,   //数据访问对象
       short port,            //绑定端口号
       const string& ip /*= ""*/) //绑定IP地址
throw (ServerException)
    :m_store(dao),m_socket(port,ip)
{

}
//数据采集
void Server::dataMine() throw (ServerException){
    //启动存储线程
    m_store.start();
    //等待客户机连接
    m_socket.acceptClient();
}
