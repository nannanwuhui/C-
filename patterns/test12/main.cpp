#include <iostream>
#include "templatemethod.h"
using namespace std;

int main()
{
    AbstractClass* pConcreateClass = new ConcreateClass;
    pConcreateClass->TemplateMethod();

    delete pConcreateClass;
    cin.get();
    return 0;
}

