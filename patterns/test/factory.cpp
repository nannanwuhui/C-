#include "factory.h"
#include <iostream>
using namespace std;

ConcreateProduct::ConcreateProduct()
{
    cout << "construction of ConcreateProduct" << endl;
}

ConcreateProduct::~ConcreateProduct()
{
    cout << "destruction of ConcreateProduct" << endl;
}


Creator::Creator()
{
    cout << "construction of Creator" << endl;
}

Creator::~Creator()
{
    cout << "destruction of Creator" << endl;
}

void Creator::AnOperation()
{
    Product* p = FactoryMethod();
    cout << "an operation of product" << endl;
    delete p;
}


ConcreateCreator::ConcreateCreator()
{
    cout << "construction of ConcreateCreator" << endl;
}

ConcreateCreator::~ConcreateCreator()
{
    cout << "destruction of ConcreateCreator" << endl;
}

Product *ConcreateCreator::FactoryMethod()
{
    cout << "ConcreateCreator::FactoryMethod() start " << endl;
    return new ConcreateProduct();
}


Product::Product()
{
    cout << "construction of Product" << endl;
}

Product::~Product()
{
    cout << "destruction of Product" << endl;
}
