#include <iostream>
#include <swift/smart_ptr/shared_ptr.hpp>
#include <swift/thread.hpp>
using namespace std;
class Thread
{
public:
    void start(){
        m_thread = thread_ptr(new swift::thread(
                                            swift::bind(&Thread::WorkProc, this)));
        m_thread->join();
        cout << "****************" << endl;
    }
protected:
    void WorkProc(){
        cout << "Hello World!" << endl;
    }
private:
    typedef swift::shared_ptr<swift::thread>	thread_ptr;
    thread_ptr m_thread;
};
int main()
{
    Thread thread;
    thread.start();
    return 0;
}

