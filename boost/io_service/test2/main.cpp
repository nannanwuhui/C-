#include <boost/asio.hpp>
#include <tea/tea.h>

int main()
{
    boost::asio::io_service io_service;
//    boost::asio::io_service::work work(io_service);//加上这一行依然可以将Counter:x打印出来
    for(int x = 0;x < 42;++x){
        io_service.poll();
        Debug("Counter:%d",x);//没有work可以打印出来
    }
    return 0;
}

