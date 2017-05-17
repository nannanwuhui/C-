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

