#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H
#include <string>
#include <list>
#include <iostream>
using namespace std;
class Flyweight{
public:
    virtual ~Flyweight(){}
    string GetIntrinsicState(){return m_state;}
    virtual void Operation(string& ExtrinsicState) = 0;
protected:
    Flyweight(const string& state):m_state(state){}
private:
    string m_state;
};

class FlyweightFactory{
public:
    FlyweightFactory(){}
    ~FlyweightFactory();
    Flyweight* GetFlyweight(const string& key);
private:
    std::list<Flyweight*> m_listFlyweight;
};

class ConcreateFlyweight : public Flyweight
{
public:
    ConcreateFlyweight(const string& state) : Flyweight(state){}
    virtual ~ConcreateFlyweight(){}
    virtual void Operation(string& ExtrinsicState){}
};
#endif // FLYWEIGHT_H

