#include <iostream>
#include <cstdio>
using namespace std;
class A
{
public:
virtual void Foo() {}	
int m_a;
};

class B : public A
{
public:
	virtual ~B() {}
};

class C
{
public:
	virtual ~C() {}
};

class D : public B, public C
{
public:
	int m_d;
};
int main(){
    cout << "sizeof(A):" << sizeof(A) << endl;//16
    cout << "sizeof(B):" << sizeof(B) << endl;//16
    cout << "sizeof(C):" << sizeof(C) << endl;//8
    cout << "sizeof(D):" << sizeof(D) << endl;//32
    return 0;
}
