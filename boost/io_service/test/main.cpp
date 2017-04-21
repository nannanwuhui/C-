#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <tea/tea.h>
using namespace std;

boost::asio::io_service io_service;
void test()
{
	Debug("hello world!");
}

void run()
{
	Debug("**** io_service.run ****");
	io_service.run();
	Debug("**** io_service.run ****");
}

int main()
{
    boost::thread thread(run);
    Debug("post");
    io_service.post(test);
    thread.join();
    return 0;
}

