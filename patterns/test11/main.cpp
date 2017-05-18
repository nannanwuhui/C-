#include <iostream>
#include "proxy.h"

using namespace std;

int main()
{
    Subject *pProxy = new Proxy();
    pProxy->Request();

    delete pProxy;
    cin.get();
    return 0;
}

