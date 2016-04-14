#include <iostream>
using namespace std;
class A{
public:
    A(void){
        cout << "A构造" << endl;
    }
    /*virtual*/ ~A(void){
        cout << "A析构" << endl;
    }
};
class B:public A{
public:
    B(void){
        cout << "B构造" << endl;
    }
    ~B(void){
        cout << "B析构" << endl;
    }
    /*~B(void){
        cout << "B析构" << endl;
    }*/
};
int main(){
    //如果new的对象类型和前面pb的类型是一样的，A类的析构函数有没有virtual都一样。
    //构造的时候先调用基类的构造函数，然后调用子类的构造函数
    //析构的时候，先调用子类的析构函数，再调用基类的析构函数
    //B* pb = new B;
    /**
     * 析构的时候只看这个指针是什么类型的，是A类型的就会去掉A类型的析构函数，
     * 是B类型的就会去调用B类型的析构函数，它不会管这个指针指向什么类型。
     * 试图去释放一个指向子类对象的基类指针的时候，可能会引起内存泄露
     */
    A* pb = new B;
    delete pb;
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/110915$ ./a.out
A构造
B构造
A析构
zn@zn-OptiPlex-9010:~/demo/110915$ g++ des.cpp 
zn@zn-OptiPlex-9010:~/demo/110915$ ./a.out
A构造
B构造
B析构
A析构
#endif
