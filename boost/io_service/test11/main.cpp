#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <tea/tea.h>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start" << std::endl;
	global_stream_lock.unlock();

	io_service->run();

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish" << std::endl;
	global_stream_lock.unlock();
}

void Dispatch( int x )
{
	global_stream_lock.lock();
	std::cout << "[" <<  boost::this_thread::get_id()  << "] "
		<< __FUNCTION__  << " x = " << x <<  std::endl;
	global_stream_lock.unlock();
}

void Post( int x )
{
	global_stream_lock.lock();
	std::cout << "[" <<  boost::this_thread::get_id()  << "] "
		<< __FUNCTION__  << " x = " << x <<  std::endl;
	global_stream_lock.unlock();
}

void Run3( boost::shared_ptr< boost::asio::io_service > io_service )
{
	for( int x = 0; x < 3; ++x )
	{
//		std::cout << "[" <<  boost::this_thread::get_id()  << "] "
//			<< __FUNCTION__ << ":" << __LINE__ << " x = " << x <<  std::endl;
		io_service->dispatch( boost::bind( &Dispatch, x * 2 ) );
//		std::cout << "[" <<  boost::this_thread::get_id()  << "] "
//			<< __FUNCTION__  << ":" << __LINE__ << " x = " << x <<  std::endl;
		io_service->post( boost::bind( &Post, x * 2 + 1 ) );
//		std::cout << "[" <<  boost::this_thread::get_id()  << "] "
//			<< __FUNCTION__  << ":" << __LINE__ << " x = " << x <<  std::endl;
//		boost::this_thread::sleep( boost::posix_time::milliseconds( 1000 ) );
	}
}

int main( int argc, char * argv[] )
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
	);

	global_stream_lock.lock();
	std::cout << "[" <<  boost::this_thread::get_id()
		<< "] The program will exit when all  work has finished." <<  std::endl;
	global_stream_lock.unlock();

	/**
	 * It should also be noted that if we had more than one worker thread,
	 * we would actually get the expected results because of the sleep call,
	 * but the problem remains still. If we removed the sleep,
	 * we might get any order of output depending on who grabbed the lock mutex first.
	 * For example, running the program without the sleep one example output received was 0, 2, 1, 4, 3, 5.
	 * We have to be aware of such things when programming at this level so we do not get fooled by "correct" output
	 * that was simply a result of having setup our program in such a way that it was possible.
	 * These types of bugs are the hardest to track down once they happen
	 * so it is imperative we fully understand the API that we are using first before diving too deep in.
	 */
	boost::thread_group worker_threads;
	for( int x = 0; x < /*1*/4; ++x )
	{
		worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
	}

	io_service->post( boost::bind( &Run3, io_service ) );

	work.reset();

	worker_threads.join_all();
	return 0;
}

