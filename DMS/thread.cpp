#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;
/**
  * 1、这里所有的线程过程函数全部都是暴露的。没有封装性
  * 线程的本质就是在一个独立的执行序列里去执行的一个函数
  * 2、把线程过程函数变成成员函数，把pthread_create放在类的内部
  * 做到这两点，线程就对象化了。
  */
//线程过程函数的规格：参数和返回值都是一个void*
void* add_run(void* arg){
    for(;;){
        cout << '+' << flush;
        usleep(5000);
    }
    return NULL;
}
void* sub_run(void* arg){
    for(;;){
        cout << '-' << flush;
        usleep(10000);
    }
    return NULL;
}
class Thread{
public:
    void start(){
        pthread_t tid;
        //但是这样的话，调用不到子类里的run了
        //我们希望在基类里面去调用一个函数，而这个函数最好在子类中能有不同
        //的实现，这就是多态了，为了实现多态就得借助于虚函数了，但是run是静态
        //函数，静态函数不可以是虚函数，虚函数要依赖于虚函数表，虚函数表存在于对象里
        //静态成员函数不依赖于对象
        //线程过程函数必须是静态的，但是又要用多态
        //调用虚函数需要调用对象，内核虽然拿不到调用对象的地址，
        //但是我们的线程过程函数里可以拿到啊
        pthread_create(&tid,NULL,run,this);
    }
    static void* run(void* arg){
        static_cast<Thread*>(arg)->run();
    }
    virtual void run() = 0;
};
/**
 * AddThread 和 SubThread，让我们看着很不爽
 * 不爽的地方就是重复的地方太多了
 * 至少start是完全一样的。一样为什么要写两遍
 * 如果两个类有共性的话，我们应该用继承来实现
 * 为什么封装后面紧接着就是继承，因为封装完了你发现，很多东西是一样的。
 * 你要做重复性封装，重复性封装体现在对象之间的共性，因为不管打印+的线程，还是打印-的
 * 线程，你毕竟都是线程，而启动这个事是线程所共有的行为，那就应该在基类里面去实现
 */
class AddThread : public Thread{
public:
#if 0
    void start(){
        pthread_t tid;
        //没有给出this指针，所以一个类的成员函数没法作为线程过程函数使用
        //线程过程函数只能是全局函数，它不能依赖于对象
        //pthread_create是c接口，没法给它调用对象
        //不过在类里面，还有一种成员函数在调用的时候不需要this指针。static
        //静态成员函数和全局函数没有什么本质性的区别，只是多了个作用域的限制
        pthread_create(&tid,NULL,run,NULL);
    }
    //成员函数不能直接调用，需要通过调用对象来调用，因为有this指针的存在
    //其实run这个成员函数有两个参数，还有一个是AddThread* this;
    static void* run(void* arg){
        for(;;){
            cout << '+' << flush;
            usleep(5000);
        }
        return NULL;
    }
#endif
    void run(){
        for(;;){
            cout << '+' << flush;
            usleep(5000);
        }
    }
};
//这样线程就不再是一个函数了，而是一个对象，这个对象里不但可以有函数，还可以
//有各式各样的成员变量，运算符重载，所有c++可以用的，都可以用在这个类里
//这样就比uc里一个单纯的回调函数变得更加丰满，里面所包含的信息可以更加丰富
class SubThread : public Thread{
public:
#if 0
    void start(){
        pthread_t tid;
        //没有给出this指针，所以一个类的成员函数没法作为线程过程函数使用
        //线程过程函数只能是全局函数，它不能依赖于对象
        //pthread_create是c接口，没法给它调用对象
        //不过在类里面，还有一种成员函数在调用的时候不需要this指针。static
        //静态成员函数和全局函数没有什么本质性的区别，只是多了个作用域的限制
        pthread_create(&tid,NULL,run,NULL);
    }
    //成员函数不能直接调用，需要通过调用对象来调用，因为有this指针的存在
    //其实run这个成员函数有两个参数，还有一个是AddThread* this;
    static void* run(void* arg){
        for(;;){
            cout << '-' << flush;
            usleep(10000);
        }
        return NULL;
    }
#endif
    void run(){
        for(;;){
            cout << '-' << flush;
            usleep(10000);
        }
    }
};
int main(){
    /*
    pthread_t tid;
    pthread_create(&tid,NULL,add_run,NULL);
    pthread_create(&tid,NULL,sub_run,NULL);
    */
    AddThread at;
    at.start();
    SubThread st;
    st.start();
    getchar();
    return 0;
}

