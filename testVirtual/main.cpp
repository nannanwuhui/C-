#include <iostream>

using namespace std;

class A
{
public:
    virtual ~A(){}
    virtual void print() = 0;
};
class B : public A{
public:
    void print()
    {
        cout << "hello B" << endl;
    }
};
class C : public B
{
public:
    void print(){
        cout << "hello C" << endl;
    }
};
int main()
{
    B *pB = new C();
    pB->print();
    A *pA = new C();
    pA->print();
    return 0;
}

