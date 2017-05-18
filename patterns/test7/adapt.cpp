#include <iostream>
#include "adapt.h"
using namespace std;

void Adapter::Request()
{
    cout << "Request of Adapter" << endl;
    SpecialRequest();
}

void Adapter::SpecialRequest()
{
    cout << "SpecialRequest of Adapter" << endl;
}
