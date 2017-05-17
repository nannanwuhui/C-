#include <iostream>
#include "prototype.h"

using namespace std;

ConcreatePrototype1::ConcreatePrototype1()
{
    cout << "construction of ConcreatePrototype1" << endl;
}

ConcreatePrototype1::ConcreatePrototype1(const ConcreatePrototype1 &other)
{
    cout << "copy construction of ConcreatePrototype1" << endl;
}

ConcreatePrototype1::~ConcreatePrototype1()
{
    cout << "destruction of ConcreatePrototype1" << endl;
}

Prototype *ConcreatePrototype1::Clone()
{
    return new ConcreatePrototype1(*this);
}


ConcreatePrototype2::ConcreatePrototype2()
{
    cout << "construction of ConcreatePrototype2" << endl;
}

ConcreatePrototype2::ConcreatePrototype2(const ConcreatePrototype2 &other)
{
    cout << "copy construction of ConcreatePrototype2" << endl;
}

ConcreatePrototype2::~ConcreatePrototype2()
{
    cout << "destruction of ConcreatePrototype2" << endl;
}

Prototype *ConcreatePrototype2::Clone()
{
    return new ConcreatePrototype2(*this);
}
