#include <iostream>
#include "proxy.h"

using namespace std;

RealSubject::RealSubject()
{
    cout << "Constructing a RealSubject" << endl;
}

void RealSubject::Request()
{
    cout << "Request By RealSubject" << endl;
}


Proxy::Proxy()
    :m_pRealSubject(NULL)
{
    cout << "Constructing a Proxy" << endl;
}

Proxy::~Proxy()
{
    delete m_pRealSubject;
    m_pRealSubject = NULL;
}

void Proxy::Request()
{
    // 需要使用 RealSubject 的时候才去初始化
    if(m_pRealSubject == NULL)
    {
        cout << "Request By Proxy" << endl;
        m_pRealSubject = new RealSubject();
    }
    m_pRealSubject->Request();
}
