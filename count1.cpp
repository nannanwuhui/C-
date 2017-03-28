#include <iostream>
#include <swift/smart_ptr/ref_counted.hpp>

using namespace std;

class MediaSessionImpl : public swift::ref_counted
{
public:
    MediaSessionImpl(){
        cout << "MediaSessionImpl()" << ":" << get_ref_count() << endl;
    }
    ~MediaSessionImpl(){
        cout << "~MediaSessionImpl()" << ":" << get_ref_count() << endl;
    }
};

class MediaSession
{
public:
    MediaSession(int count = 1) : m_pImpl(0),m_count(count){
        cout << "MediaSession():m_pImpl(0)" << ":" << m_count << endl;
    }
    MediaSession(MediaSessionImpl* impl) : m_pImpl(impl){
        cout << "MediaSession(MediaSessionImpl* impl)!" << ":" << m_pImpl->get_ref_count() << endl;
    }
    MediaSession(const MediaSession& other){
        cout << "MediaSession(const MediaSession& other)" << endl;
        if(other.m_pImpl)
            other.m_pImpl->inc_ref();
        m_pImpl = other.m_pImpl;
    }
    ~MediaSession(){
        cout << "~MediaSession()" << ":" << m_count << ":" << "ref_count:" << m_pImpl->get_ref_count() << endl;
        if(m_pImpl)
            m_pImpl->dec_ref();
    }

    MediaSession& operator= (const MediaSession& other){
        cout << "operator=" << endl; 
        if(m_pImpl != other.m_pImpl)   
        {
            if(m_pImpl)
                m_pImpl->dec_ref();
            if(other.m_pImpl)
                other.m_pImpl->inc_ref();
            m_pImpl = other.m_pImpl;
        }
        return *this;
    }
    void print_ref_count(){
        cout << "ref_count:" << m_pImpl->get_ref_count() << endl;    
    }
private:
    MediaSessionImpl* m_pImpl;
    int m_count;
};
int main(){
    MediaSession media(new MediaSessionImpl());
    //MediaSession media1 = media; 
    MediaSession media1(media); 
    media.print_ref_count();
    media1.print_ref_count();
    //media = MediaSession();
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/042816$ ls
a.out  count.cpp  test.cpp
zn@zn-OptiPlex-9010:~/demo/042816$ g++ count.cpp -I /home/zn/bqvision/clearvision/linux_x86_64/debug/include -lswift-1.0.0-gcc -L/home/zn/bqvision/clearvision/linux_x86_64/debug/lib
zn@zn-OptiPlex-9010:~/demo/042816$ ./a.out
./a.out: error while loading shared libraries: libswift-1.0.0-gcc.so: cannot open shared object file: No such file or directory
zn@zn-OptiPlex-9010:~/demo/042816$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/zn/bqvision/clearvision/linux_x86_64/debug/lib
zn@zn-OptiPlex-9010:~/demo/042816$ echo $LD_LIBRARY_PATH
:/home/zn/bqvision/clearvision/linux_x86_64/debug/lib
zn@zn-OptiPlex-9010:~/demo/042816$ ./a.out 
MediaSessionImpl():1
MediaSession(MediaSessionImpl* impl)!:1
MediaSession(const MediaSession& other)
ref_count:2
ref_count:2
~MediaSession():4205504:ref_count:2
~MediaSession():0:ref_count:1
~MediaSessionImpl():0
#endif
