#include <tea/tea.h>
class A{
public:
    A(int x = 0){
        Debug("A()");
    }
    A(const A& a){
        Debug("拷贝构造");
        m_x = a.m_x;
    }
    A& operator= (const A& other){
        Debug("拷贝赋值");
        if(this != &other){
            m_x = other.m_x;
        }
        return *this;
    }
    ~A(){
        Debug("~A()");
    }
    void print(){
        Debug("%d",m_x);
    }
private:
    int m_x;
};
class B{
public:
    B(A a)/*:m_a(a)*/{
        m_a = a;
        Debug("B(A a)");
    }
    ~B(){
        Debug("~B()");
    }
    void print(){
        m_a.print();
    }
private:
    A m_a;
};
int main()
{
    Debug("****");
    B b(A(5));//这里的拷贝需要先创建临时对象
    b.print();
    return 0;
}
#if 0
１、打印信息
[20640][2017.4.24 13:40:48.987978][17280 days 05:40:48][DEBUG](../test12/main.cpp:36)****
[20640][2017.4.24 13:40:48.988247][17280 days 05:40:48][DEBUG](../test12/main.cpp:5)A()
[20640][2017.4.24 13:40:48.988260][17280 days 05:40:48][DEBUG](../test12/main.cpp:8)拷贝构造
[20640][2017.4.24 13:40:48.988270][17280 days 05:40:48][DEBUG](../test12/main.cpp:23)B(A a)
[20640][2017.4.24 13:40:48.988279][17280 days 05:40:48][DEBUG](../test12/main.cpp:12)~A()
[20640][2017.4.24 13:40:48.988303][17280 days 05:40:48][DEBUG](../test12/main.cpp:15)4197024
[20640][2017.4.24 13:40:48.988310][17280 days 05:40:48][DEBUG](../test12/main.cpp:26)~B()
[20640][2017.4.24 13:40:48.988317][17280 days 05:40:48][DEBUG](../test12/main.cpp:12)~A()
2、
类成员初始化可以在构造函数当中实现，也可以在构造函数的初始化列表当中实现。但高手则一般选择后者，是什么原因呢？

// 构造函数当中的实现
CMyObject :: CMyObject (int id, string name)
{
    m_id = id;
    m_name = name;
}

// 初始化列表中的实现
CMyObject::CMyObject(int id, string name)
      : m_id(id), m_name(name)
{
}


优势：省去了临时对象的存在

方法一是在构造函数当中做赋值的操作，而方法二是做纯粹的初始化操作。我们都知道，C++的赋值操作是会产生临时对象的。临时对象的出现会降低程序的效率。


其它场景：

1. 类中存在const成员，那么该成员必须在初始化列表中做初始化。

2. 类中含有其它类B作为成员，而B类禁止掉赋值操作的情况下，那么对B的对象也只能通过初始化列表来实现。
#endif

