#include <iostream>
using namespace std;
int add(int a,int b){
    cout << "add(1)" << endl;
    return a + b;
}
double add(double a,double b){
    cout << "add(2)" << endl;
    return a + b;
}
void foo(int n,void *p){
    cout << "foo(1)" << endl;
}
void foo(double f,...){
    cout << "foo(2)" << endl;
}
int main(){
    cout << add(10,20) << endl;
    cout << add(0.1,0.2) << endl;
    // cout << add(10,0.3) << endl;
    double f;
    void* p;
    foo(f,p);
    int (*pfunc)(int,int) = add;
    pfunc(100,200);
    return 0;
}
#if 0
１）重载
在同一作用域中，函数名相同，形参表不同的函数可以有多个，它们构成重载关系，返回值一样不一样都可以。
函数名相同，形参表相同，但是常属性不同的成员函数也可以构成重载关系
把int转成double的时候会损失精度，把double转成int的时候会损失小数。
char=>int
short=>int
short=>long
float=>double(升级转换)
选择最安全，改变最小的，工作量最少的。
升级转换　　标准转换　自定义转换　省略号

重载匹配的原则：
完全匹配>常量转换（变量转换成const）>升级转换>标准转换（int=>double,char=>long，基本类型之间的转换）>自定义转换>省略号匹配（匹配度最差）
函数名就是函数地址
根据函数指针类型进行匹配
C++换名：（编译器阶段）
参数表的不同：类型，个数，顺序
add_int_int（为了重载，不考虑返回值）
add_double_double
c的编译器不会换名，那么当用c++编译器编译的一个库给c调用的时候就会出现问题，它找不到add这个函数名。
extern “C”:用c的编译器去处理,也就是说extern C所包含的代码不会再去进行c++换名了
extern “C”{
	放在这里面的代码就不会再去进行c++的换名了，当然也就不能进行重载了。
	void foo(int n,char c){...}//foo
}
这个extern C主要是应用在c调用c++的场合。
#endif 
