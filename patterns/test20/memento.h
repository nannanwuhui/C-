#ifndef MEMENTO_H
#define MEMENTO_H
#include <string>
#include <iostream>
using namespace std;
class Memento;
class Originator
{
public:
    Originator(const string& state);
    Originator(){}
    virtual ~Originator(){}
    Memento* createMemento();
    string getState();
    void setState(const string& state);
    void restoreState(Memento *pMemento);
    void printState();
private:
    string m_state;
};
// 把 Memento 的接口函数都设置为私有的,而 Originator 是它的友元,
// 这样保证了只有 Originator 可以对其访问
class Memento
{
private:
    friend class Originator;
    Memento(const string& state);
    void setState(const string& state);
    string getState();
    string m_state;
};
#endif // MEMENTO_H
