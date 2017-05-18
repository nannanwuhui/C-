#include "composite.h"
#include <iostream>
#include <algorithm>

using namespace std;


void Leaf::Operation()
{
    cout << "Operation by leaf" << endl;
}


Composite::~Composite()
{
    std::list<Component*>::iterator iter = m_ListOfComponent.begin();
    for(;iter != m_ListOfComponent.end();iter++){
        delete(*iter);
    }
}

void Composite::Operation()
{
    cout << "Operation by Composite" << endl;
    std::list<Component*>::iterator iter = m_ListOfComponent.begin();
    for(;iter != m_ListOfComponent.end();iter++){
        (*iter)->Operation();
    }
}

void Composite::Add(Component *pChild)
{
    m_ListOfComponent.push_back(pChild);
}

void Composite::Remove(Component *pChild)
{
    std::list<Component*>::iterator iter;
    iter = find(m_ListOfComponent.begin(),m_ListOfComponent.end(),pChild);
    if(iter != m_ListOfComponent.end()){
        m_ListOfComponent.erase(iter);
    }
}

Component *Composite::GetChild(int nIndex)
{
    if (nIndex <= 0 || nIndex > m_ListOfComponent.size()){
        return NULL;
    }
    std::list<Component*>::iterator iter = m_ListOfComponent.begin();
    for(int i = 1;iter != m_ListOfComponent.end();iter++,i++){
        if(i == nIndex){
            break;
        }
    }
    return *iter;
}
