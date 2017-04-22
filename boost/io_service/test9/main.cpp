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
size_t fib(size_t n){
    if(n <= 1){
        return n;
    }
    boost::this_thread::sleep( boost::posix_time::milliseconds(1000) );
    return fib( n-1 ) + fib( n-2 );
}
void CalculateFib( size_t n ){
    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] Now calculating fib(" << n << ")" << endl;
    global_stream_lock.unlock();

    size_t f = fib(n);

    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] fib("<< n << ")=" << f << endl;
    global_stream_lock.unlock();
}
int main()
{
    boost::shared_ptr< boost::asio::io_service > io_service( new boost::asio::io_service );
    boost::shared_ptr< boost::asio::io_service::work> work( new boost::asio::io_service::work(*io_service) );
    global_stream_lock.lock();
    cout << "[" << boost::this_thread::get_id() << "] The program will exit when all work has finished." << endl;
    global_stream_lock.unlock();

    boost::thread_group worker_threads;
    for(int x = 0; x < 2;++x){
        worker_threads.create_thread( boost::bind(&WorkerThread,io_service) );
    }

    io_service->post( boost::bind(CalculateFib,3) );
    io_service->post( boost::bind(CalculateFib,4) );
    io_service->post( boost::bind(CalculateFib,5) );

    work.reset();
    worker_threads.join_all();
    return 0;
}

