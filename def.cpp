#include <iostream>
using namespace std;
void foo(void){

}
void foo(int n = 0,double f = 0.1,char c = 'X');
void bar(int,double,char)
{
    cout << "bar(3)" << endl;
}
void bar(int){
    cout << "bar(1)" << endl;
}
void bar(void)
{
    cout << "bar(2)" << endl;
}
int main(){
    foo(10,3.14,'A');
    foo(10,3.14);
    foo(10);
    //foo();//重载和缺省发生了冲突，两个函数都行
    //foo(10,,'B');//这样不行
    bar(100);
    bar();
    bar(100,3.14,'C');
    return 0;
}
void foo(int n,double f,char c){
    cout << n << "," << f << ","<< c << endl;
}
#if 0
３、哑元
void JPEG2BMP(int n){...};//V1.0
void JPEG2BMP(void){...};//V2.0
void JPEG2BMP(int){...};//V2.0
JPEG2BMP(20);
比如说这样的一个场景，公司做一个图形处理的库，给很多用户，实现的v1.0版的JPEG2BMP需要一个参数，但是现在版本升级了，不需要这个参数了，这个时候用void　JPEG2BMP(void){...};//V2.0
这样的话，所有的用户的代码都要改，这样的成本是很高的，可能用户宁愿用v1.0版的也不用v2.0版的，这个时候就可以使用哑元，void JPEG2BMP(int){...};//V2.0，虽然我们不用，但是占了这个位置，所有的用户的代码都不需要改。
(向后兼容的情况)
（重载的情况）那为什么不能用不同的函数名来区分呢。bar1,bar2
很多时候函数名是不能变的，只能通过参数表来区分。
i++
++i
operator++
operator++(int)

哑元是一种没有参数名的参数。主要是为了函数的区别和向前兼容。
#endif
