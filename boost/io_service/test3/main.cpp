#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <tea/tea.h>
int main()
{
    boost::asio::io_service io_service;
    boost::shared_ptr< boost::asio::io_service::work > work(new boost::asio::io_service::work(io_service));
    work.reset();
    io_service.run();
    Debug("Do you reckon this line displays?");//这句话会被打印出来
    return 0;
}

