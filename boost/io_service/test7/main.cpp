#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <tea/tea.h>

void WorkerThread(boost::shared_ptr< boost::asio::io_service > io_service){
    Debug("Thread Start");
    io_service->run();
    Debug("Thread Finish");
}
int main()
{
    boost::shared_ptr< boost::asio::io_service > io_service(new boost::asio::io_service);
    boost::shared_ptr< boost::asio::io_service::work > work(new boost::asio::io_service::work(*io_service));
    Debug("Press [Enter] to exit.");
    boost::thread_group worker_threads;
    for(int x = 0; x < 4;x++){
        worker_threads.create_thread( boost::bind(&WorkerThread,io_service) );
    }
    std::cin.get();
    io_service->stop();
    worker_threads.join_all();
    return 0;
}

