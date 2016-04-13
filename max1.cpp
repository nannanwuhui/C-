#include <iostream>
using namespace std;
/**
 * 算法与类型无关
 * 但却不得不为每个类型分别实现一个函数,因为类型限定
 * 强类型语言始终都要关注类型
 * 如何让算法和类型脱离呢?
 */
int max_int(int x,int y){
    return x>y?x:y;
}
string max_str(string x,string y){
    return x>y?x:y;
}
int main(void){
    cout << max_int(100,200) << endl;
    cout << max_str("hello","world") << endl;
    return 0;
}
#if 0
模板与STL(标准模板库)
c,c++强类型语言或者称为静态类型语言
int x;
x = 100;
x = “hello”;?//不行
Student s(...);
Teacher t(...);
s = t;?
void foo(const Student& s){...}
foo(t);?//不行
类型安全，用类型来描述对象，体现面向对象的思想。
OOP（通过类型来实现的，）
类型决定对象的行为，外观（属性）和接口。
缺陷：类型性的约束，通过类型来表达一切的做法，使得很多本来和类型无关的过程，或者与类型无关的语意因为类型的约束而不得不变得专有化。
#endif

