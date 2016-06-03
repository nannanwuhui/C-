#include <iostream>
using namespace std;
class A {
    public:
        int a;
        virtual void v();
};

class B: virtual public A{                       //virtual inheritance here
    public:
        int b;
        virtual void w();
};
int main(){
    cout << "sizeof(A):" << sizeof(A) << endl;//16
    cout << "sizeof(B):" << sizeof(B) << endl;//32
}
