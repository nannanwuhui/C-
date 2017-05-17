#include <iostream>
#include "singleton.h"
using namespace std;
// 类的静态成员变量要在类体外进行定义
Singleton* Singleton::m_pStatic = NULL;

Singleton *Singleton::GetInstancePtr()
{
    if(NULL == m_pStatic){
        m_pStatic = new Singleton();
    }
    return m_pStatic;
}

Singleton Singleton::GetInstance()
{
    return *GetInstancePtr();
}

void Singleton::Test()
{
    cout << "**** Test ****" << endl;
}


