#include <iostream>
#include "adapt.h"
using namespace std;

int main()
{
    Adaptee *pAdaptee = new Adaptee;
    Target *pTarget = new Adapter(pAdaptee);
    pTarget->Request();
    delete pTarget;
    cin.get();
    return 0;
}
#if 0
作用:
将一个类的接口转换成客户希望的另外一个接口。Adapt 模式使得原本由于接
口不兼容而不能一起工作的那些类可以一起工作。
#endif
