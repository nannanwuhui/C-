#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
boost::mutex global_stream_lock;
void WorkerThread(boost::shared_ptr< boost::asio::io_service > io_service){
    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] Thread Start" << endl;
    global_stream_lock.unlock();

    io_service->run();

    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] Thread Finish" << endl;
    global_stream_lock.unlock();
}
int main()
{
    boost::shared_ptr< boost::asio::io_service > io_service( new boost::asio::io_service );
    boost::shared_ptr< boost::asio::io_service::work> work( new boost::asio::io_service::work(*io_service) );
    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] Press [Enter] to exit." << endl;
    global_stream_lock.unlock();

    boost::thread_group worker_threads;
    for(int x = 0; x < 4;++x){
        worker_threads.create_thread( boost::bind(&WorkerThread,io_service) );
    }

    std::cin.get();
    io_service->stop();
    worker_threads.join_all();
    return 0;
}

