#include <iostream>
#include "decorator.h"
using namespace std;


Decorator::~Decorator()
{
    delete m_pComponent;
    m_pComponent = NULL;
}


void ConcreateComponent::Operation()
{
    cout << "Operation of ConcreateComponent" << endl;
}


void ConcreateDecorator::Operation()
{
    m_pComponent->Operation();
    AddedBehavior();
}

void ConcreateDecorator::AddedBehavior()
{
    cout << "AddedBehavior of ConcreateDecorator" << endl;
}

