#include <iostream>
using namespace std;
class MediaSession
{
public:
    MediaSession(int a = 0):m_pImpl(0),m_a(a){
        cout << "MediaSession()" << endl;
    }
    MediaSession(int *impl):m_pImpl(impl){
        cout << "MediaSession(int *impl)" << endl;
    }
    MediaSession(const MediaSession &other)
    {
        m_pImpl = other.m_pImpl;
        cout << "MediaSession(const MediaSession &other)" << endl;
    }
    void setA(int a){
        m_a = a;
    }
    ~MediaSession(){
        cout << " ~MediaSession() m_a:" << m_a << endl;
    }
private:
    int* m_pImpl;
    int m_a;
};
int main(){
    MediaSession media = MediaSession(new int(10));
    /*
     * 这里MediaSession(1)是构造出一个临时变量,然后将这个临时变量赋给media,
     * 离开这一行这个临时变量就会被析构
     */
    media = MediaSession(1);
    media.setA(2);
    cout << "hello world!" << endl;
    return 0;
}
