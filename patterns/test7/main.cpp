#include <iostream>
#include "adapt.h"
using namespace std;

int main()
{
    Target *pTarget = new Adapter();
    pTarget->Request();
    delete pTarget;
    cin.get();
    return 0;
}

