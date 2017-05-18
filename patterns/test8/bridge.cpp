#include <iostream>
#include "bridge.h"

using namespace std;

Abstraction::Abstraction(Implementor *pImplementor)
    :m_pImplementor(pImplementor)
{

}

Abstraction::~Abstraction()
{
    delete m_pImplementor;
    m_pImplementor = NULL;
}

void Abstraction::Operation()
{
    m_pImplementor->OperationImpl();
}


void ConcreateImplementorA::OperationImpl()
{
    cout << "Implementation by ConcreateImplementorA" << endl;
}


void ConcreateImplementorB::OperationImpl()
{
    cout << "Implementation by ConcreateImplementorB" << endl;
}
