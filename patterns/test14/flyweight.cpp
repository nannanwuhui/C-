#include "flyweight.h"



FlyweightFactory::~FlyweightFactory()
{
    list<Flyweight*>::iterator it = m_listFlyweight.begin();
    for(;it != m_listFlyweight.end();it++){
        delete(*it);
    }
    m_listFlyweight.clear();
}

Flyweight *FlyweightFactory::GetFlyweight(const string &key)
{
    list<Flyweight*>::iterator it = m_listFlyweight.begin();
    for(;it != m_listFlyweight.end();it++){
        if((*it)->GetIntrinsicState() == key){
            cout << "The Flyweight:" << key << " already exits" << endl;
            return (*it);
        }
    }
    cout << "Creating a new Flyweight:" << key << endl;
    Flyweight* flyweight = new ConcreateFlyweight(key);
    m_listFlyweight.push_back(flyweight);
    return flyweight;
}
