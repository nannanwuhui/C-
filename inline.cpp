#include <iostream>
using namespace std;
//预编译阶段 文本替换，不计算表达式,宏没有类型检查，但是速度快
//函数调用有开销，但是可以有类型检查
//#define SQUARE(X) ((X)*(X))
//编译器，会计算表达式，把结果传给实参
//用内联函数的话，还是按照函数来处理的，编译器该做类型检查做类型检查，该计算表达式计算表达式，会把编译好的二进制代码嵌入函数所在的地方。
//但是如果是普通的函数调用的话，是在运行到调用函数的时候，才在进程映像中的栈空间为函数单独开一个函数栈。内联函数直接嵌入可执行程序，
//省去了函数调用的开销，但是生成的可执行程序a.out肯定会变大
inline int SQUARE(int X)
{
    return X*X;
}
int main(){
    cout << SQUARE(2+3) << endl;
    return 0;
}
#if 0
４）内联函数（二进制代码会变大）
A.可以在获得函数调用的优势（计算实参表达式，类型检查等等）的同时，提供接近于宏的性能。
B.inline关键字可以将一个函数声明为内联，但是inline只是建议编译器，未必真的将其处理为内联。到底是不是内联由编译器决定。
复杂函数不适合做内联。调用的时间远远小于执行的时间，就算做了内联，节省的时间很少。
递归函数不能做内联。
void foo(void)
{
	if(...)
		foo();
}
高地址
栈　　　　局部变量，函数参数以及返回值（放在函数的栈空间里）等，每调用一个函数，都会创建一个栈空间
堆　　malloc就会分配一块内存，只要不free，就始终在
全局区（静态存储区）全局变量，静态变量，常量
代码段 main() square()
低地址

堆和栈的大小不是固定，会随着程序的执行，上下浮动
当调用函数的时候，就会在栈里开辟一块内容归这个函数使用，当函数结束的时候，这块内容就被回收，
函数的局部变量和参数都被放在栈里，而全局变量被放在全局区，所有函数结束后，这个值仍然存在。
C.隐式内联和显示内联
通过inline关键字声明的内联函数－－显示内联
直接在类／结构的声明部分定义的成员函数－－隐式内联
编译器编译的时候决定是不是真的内联。
#endif
