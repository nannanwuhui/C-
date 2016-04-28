#include <iostream>
#include <swift/smart_ptr/ref_counted.hpp>

using namespace std;

class MediaSessionImpl : public swift::ref_counted
{
public:
    MediaSessionImpl(){}
    ~MediaSessionImpl(){}
};

class MediaSession
{
public:
    MediaSession() : m_pImpl(0){}
    MediaSession(MediaSessionImpl* impl) : m_pImpl(impl){
        cout << "MediaSession(MediaSessionImpl* impl)!" << endl;
    }
    MediaSession(const MediaSession& other){
        if(other.m_pImpl)
            other.m_pImpl->inc_ref();
        m_pImpl = other.m_pImpl;
    }
    ~MediaSession(){
        cout << "~MediaSession()" << endl;
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

private:
    MediaSessionImpl* m_pImpl;
};
int main(){
    MediaSession media(new MediaSessionImpl());
    media = MediaSession();
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
MediaSession(MediaSessionImpl* impl)!
operator=
~MediaSession()
~MediaSession()
zn@zn-OptiPlex-9010:~/demo/042816$
#endif
