#include <iostream>
using namespace std;
class Foo
{
public:
    Foo(string str):m_string(str){}
    void print(){
        cout << m_string << endl; 
    }
private:
    string m_string;
};
int main(){
    //引用常量必须使用const型引用
    const string& x = "hello"; 
    //引用即别名，以下两种实例化的方式没有区别
    Foo f1(x);
    f1.print();
    Foo f2("hello");
    f2.print();
    return 0;
}
