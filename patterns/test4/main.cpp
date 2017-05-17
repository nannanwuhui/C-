#include <iostream>
#include "singleton.h"
using namespace std;

int main(){
    // 不用初始化类对象就可以访问了
    Singleton::GetInstancePtr()->Test();
    Singleton::GetInstance().Test();
    cin.get();
    return 0;
}
#if 0
常见设计模式的解析和实现(C++)之五-Singleton 模式
作用:保证一个类仅有一个实例,并提供一个访问它的全局访问点。
解析:
Singleton 模式其实是对全局静态变量的一个取代策略,上面提到的 Singleton
模式的两个作用在 C++中是通过如下的机制实现的:1)仅有一个实例,提供一个
类的静态成员变量,大家知道类的静态成员变量对于一个类的所有对象而言是惟
一的 2)提供一个访问它的全局访问点,也就是提供对应的访问这个静态成员变
量的静态成员函数,对类的所有对象而言也是惟一的.在 C++中,可以直接使用类
域进行访问而不必初始化一个类的对象.
下面的实现其实是 Singleton 的一个简单实现,并不是特别的通用,一般的,如果
一个项目中需要使用到 Singleton 模式比较多的话,那么一般会实现一个 Singl
eton 的模板类,模板类的模板参数是需要采用 Singleton 模式的类,比如这样实
现:
template<typename T>
class Singleton
{
//
.类的声明
};
// 需要采用 singleton 模式的类
class Test
: public Singleton<Test>
{
//
类的声明
};
但是,我们的实现还是采用最简单的实现办法,起的是演示的作用
#endif
