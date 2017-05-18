#include <iostream>
#include "templatemethod.h"
using namespace std;

void AbstractClass::TemplateMethod()
{
    PrimitiveOperation1();
    PrimitiveOperation2();
}


void ConcreateClass::PrimitiveOperation1()
{
    cout << "PrimitiveOperation1 by ConcreateClass" << endl;
}

void ConcreateClass::PrimitiveOperation2()
{
    cout << "PrimitiveOperation2 by ConcreateClass" << endl;
}
