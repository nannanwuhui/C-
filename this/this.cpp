#include <iostream>
using namespace std;
class Student{
public:
   /* Student(const string& strName,int nAge):m_strName(strName),m_nAge(nAge){
        cout << "在构造函数中：" << this << endl; 
    }*/
    /**
     * 这种情况下，编译器可以分的清楚，strName括号外边的是成员变量，而在（）里面的是形参
     */
    /*Student(const string& strName,int nAge):strName(strName),nAge(nAge){
        cout << "在构造函数中：" << this << endl; 
    }*/
    Student(const string& strName,int nAge){
        cout << "在构造函数中：" << this << endl;
        /**
         * 形参是局部变量，形参的作用域要比类成员变量的作用域要小
         * 所以这里的strName,nAge都会被理解成是形参，
         * 在c++里,全局变量>成员变量>局部变量(作用域)
         * 成员变量的作用域是整个类，而形参的作用域只是所在的函数
         * 作用域小的会隐藏作用域大的。
         */
        this->strName = strName;
        this->nAge = nAge;
    }
    void Print(){
        cout << "在Print()函数中：" << this << endl;
        cout << strName << "," << nAge << endl;
    }
private:
    //string m_strName;
    //int m_nAge;
    string strName;
    int nAge;
};
int main(){
    Student s("张飞",28);
    //对类类型的对象取地址&s
    cout << "在main()函数中：" << &s << endl;
    s.Print();
    return 0;
}
#if 0
3、this指针
class A{
	void  foo(B b){...}
};
class B{};
A a;
B b;
a.foo(b);
a:调用对象
b:参数对象
1）一般而言，关键字this表示一个指针，对于一般成员函数，该指针指向调用对象，而对于构造函数，它指向这个正在构造的对象。
2）this指针可用于在构造函数中区分与构造参数名相同的成员变量
#endif
