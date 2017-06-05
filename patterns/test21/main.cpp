#include <iostream>
#include "visitor.h"
using namespace std;

int main()
{
//    Visitor *pVisitor = new ConcreateVisitorA();
    Visitor *pVisitor = new ConcreateVisitorB();
//    Element *pElement = new ConcreateElementA();
    Element *pElement = new ConcreateElementB();
    pElement->accept(*pVisitor);

    delete pElement;
    delete pVisitor;
    return 0;
}

