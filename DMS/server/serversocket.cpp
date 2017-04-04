//实现服务器套接字类
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#include "serversocket.h"
#include "clientthread.h"

ServerSocket::ServerSocket(short port,//绑定端口号
             const string& ip /*= ""*/)//绑定IP地址
throw(SocketException){
    cout << "初始化服务器开始..." << endl;
    if((m_sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
        throw SocketException("创建套接字失败");
    }
    /**
     * １、将服务器停掉然后马上启动，有时候会失败。
     * 是绑定的时候失败了。是因为服务器的地址和端口的这个地址结构不能马上释放。
     * 服务停掉，进程没有了，但是内核的协议栈里面还记着这个状态，状态是time_wait，
     * 等候状态，它有一个延迟，只有等这个延迟时间到了以后，才能真的把这个地址资源给释放了。
     * 你才能再次绑定这个地址和端口。那就需要等一段时间。
     * 如果你不想等，你想让服务器直接起来。调用setsockopt();设置套接字选项。
     * ２、当你设置不同类型东西的不同选项的时候，后面两个参数的类型是不一样的。
     * 有的用的是整数，有的用的是结构体，有的用的可能是个short,c++里面有这个重载，
     * 我可以用不同的类型来对应不同的函数，但是c里面没有重载，c里面就用一个所谓
     * 的泛型指针来支持，也就是说setsockopt()的第三个参数是一个void*,所以你可以
     * 给它传递任何类型的指针，这个变量有多大靠第四个参数来告诉它。
     * 这样就可以给不同的选项指定不同类型的变量来表示不同的含义了。
     * 第三个参数虽然是一个指针，但是它依然是个输入参数。不是输出参数。
     * 之所以它接受的是一个指针，而不是变量值的原因就是为了做到泛型。
     * 因为void*可以指向任何类型。
     */
    int on = 1;
    //成功返回０，失败返回-1
    if(setsockopt(m_sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) == -1){
        throw SocketException("设置地址重用失败");
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    //#define	INADDR_ANY		((in_addr_t) 0x00000000)
    //对于0来说，不管是主机字节序还是网络字节序都是一样的
    addr.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
    //sockaddr_in,sockaddr_un都是在sockaddr的基础上增加了一些东西，
    //所以可以把sockaddr看做是sockaddr_in,sockaddr_un的基类。
    //任何一个子类对象都可以隐式的转换成基类对象
    //使用的时候可以用第一个参数addr.sin_family的值逆向造型成子类（sockaddr_in,sockaddr_un）。
    if(bind(m_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1){
        throw SocketException("绑定套接字失败");
    }
    //绑定的目的就是把逻辑对象(socket)和物理对象port连起来。
    //因为客户端连接不是和socket连接，是和port连接，这样客户端和服务器的
    //端口发起connect，服务器的socket才能感觉到。
    if(listen(m_sockfd,1024) == -1){//1024不是最大连接数，而是最大未决连接请求数
        throw SocketException("侦听套接字失败");
    }
    cout << "初始化服务器开完成..." << endl;
}
//等待客户机连接
void ServerSocket::acceptClient()throw(SocketException){
    cout << "等待客户机的连接..." << endl;
    //循环阻塞
    for(;;){
        sockaddr_in addrcli;
        socklen_t addrlen = sizeof(addrcli);
        //每接受一个客户机的连接请求...
        int connfd = accept(m_sockfd,(sockaddr*)&addrcli,&addrlen);
        if(connfd == -1){
            close(m_sockfd);
            throw SocketException("接受连接请求失败");
        }
        //即创建一个客户线程为其提供服务
        (new ClientThread(connfd))->start();
    }
}
