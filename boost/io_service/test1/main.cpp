#include <boost/asio.hpp>
#include <iostream>

using namespace std;

int main()
{
    boost::asio::io_service io_service;
//    boost::asio::io_service::work work( io_service );//加上这句话，io_service.run()就会阻塞
    io_service.run();
    cout << "Hello World!" << endl;//"Do you reckon this line displays?"没有work，不阻塞
    return 0;
}

