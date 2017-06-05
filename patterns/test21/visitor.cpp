#include <iostream>
#include "visitor.h"
using namespace std;


void ConcreateElementA::accept(Visitor &visitor)
{
    visitor.visitConcreateElementA(this);
}


void ConcreateElementB::accept(Visitor &visitor)
{
    visitor.visitConcreateElementB(this);
}


void ConcreateVisitorA::visitConcreateElementA(ConcreateElementA *pConcreateElementA)
{
    cout << "VisitConcreateElementA By ConcreateVisitorA" << endl;
}

void ConcreateVisitorA::visitConcreateElementB(ConcreateElementB *pConcreateElementB)
{
    cout << "VisitConcreateElementB By ConcreateVisitorA" << endl;
}


void ConcreateVisitorB::visitConcreateElementA(ConcreateElementA *pConcreateElementA)
{
    cout << "VisitConcreateElementA By ConcreateVisitorB" << endl;
}

void ConcreateVisitorB::visitConcreateElementB(ConcreateElementB *pConcreateElementB)
{
    cout << "VisitConcreateElementB By ConcreateVisitorB" << endl;
}
