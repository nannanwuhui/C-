#include "memento.h"



Originator::Originator(const string &state)
    :m_state(state)
{

}

Memento *Originator::createMemento()
{
    return new Memento(m_state);
}

string Originator::getState()
{
    return m_state;
}

void Originator::setState(const string &state)
{
    m_state = state;
}

void Originator::restoreState(Memento *pMemento)
{
    if(pMemento != NULL){
        m_state = pMemento->getState();
    }
}

void Originator::printState()
{
    cout << "state=" << m_state << endl;
}


Memento::Memento(const string &state)
    :m_state(state)
{

}

void Memento::setState(const string &state)
{
    m_state = state;
}

string Memento::getState()
{
    return m_state;
}
