#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <tea/tea.h>
#include <iostream>

boost::asio::io_service io_service;
void WorkerThread(){
    Debug("Thread Start");
    io_service.run();
    Debug("Thread Finish");
}
int main()
{
    boost::shared_ptr< boost::asio::io_service::work > work(new boost::asio::io_service::work(io_service));
    boost::thread_group worker_threads;
    Debug("Press [Enter] to exit.");
    for(int x = 0; x < 4;x++){
        worker_threads.create_thread(WorkerThread);
    }
    std::cin.get();
    io_service.stop();
    worker_threads.join_all();
    return 0;
}

