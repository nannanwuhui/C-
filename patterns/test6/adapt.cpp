#include <iostream>
#include "adapt.h"
using namespace std;


void Adaptee::SpecialRequest()
{
    cout << "SpecialRequest of Adaptee" << endl;
}


Adapter::Adapter(Adaptee *pAdaptee)
    :m_pAdaptee(pAdaptee)
{

}

Adapter::~Adapter()
{
    delete m_pAdaptee;
    m_pAdaptee = NULL;
}

void Adapter::Request()
{
    cout << "Request of Adapter" << endl;
    m_pAdaptee->SpecialRequest();
}
