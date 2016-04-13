#include <iostream>
#include <typeinfo>
#include <cstring>
using namespace std;
/**
 * 这就是传说中的函数模板
 * 以前用的都是值参数
 * 这里用的是类型参数,类型参数化
 * T是类型形参
 * template<class T> 这样也可以，这是老的写法，最好写成typename
 * 注意类型参数是放在<>里面的
 * 类里面的成员函数的返回值，成员函数的参数，成员函数的局部变量，成员变量，类的基类统统都可以
 * 参数化,这样得到的模板就是类模板
 *
 */
//通用版本
template<typename T>  //类似宏定义
T max(T x,T y){       //类似宏替换
    cout << typeid(T).name() << endl;
    return x > y ? x : y;
}
/**
 * 当类型实参是const char *的时候，不要用上面通用的版本，
 * 而是用如下的版本
 */
/**
 * 针对const char*的特化版本,特化版本是不得已而为之的版本,
 * 能用通用版本，尽量不用特化版本
 * 这里max<const char*>中的const char*可以省略
 * template<>有的编译器也可以不写，但是最好写上，因为不写的话，
 * 就和一个普通的函数每什么区别了
 */
template<>
const char * max<const char *>(const char* x,const char* y){
    cout << "const char*" << endl;
    return strcmp(x,y)>0 ? x : y;
}
int main(void){
    /**
     * max<int>这里的int是类型实参
     */
    //cout << ::max<int>(100,200) << endl;
    /**
     * 隐式推断,推断出来类型参数的类型
     */
    cout << ::max(100,200) << endl;
    //cout << ::max<string>("hello","world") << endl;
    /**
     * 这个会被隐式推断成const char *,还是会比较两个地址
     * ./a.out  PKc (pointer  const(谐音K,因为c已经用过了)    char)
     */
    cout << ::max("hello","world") << endl;
    /**
     * 这样写还不如::max<string>("hello","world")
     */ 
    cout << ::max(string("hello"),string("world")) << endl;
    //cout << ::max<double>(3.14,5.66) << endl;
    cout << ::max(3.14,5.66) << endl;
    return 0;
}
