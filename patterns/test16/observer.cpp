#include "observer.h"
#include "algorithm"



Subject::~Subject()
{
    list<Observer*>::iterator it = m_listObserver.begin();
    for(;it != m_listObserver.end();it++){
        delete(*it);
    }
    m_listObserver.clear();
}

void Subject::Notify()
{
    cout << "Notify Observers's State" << endl;
    list<Observer*>::iterator it = m_listObserver.begin();
    for(;it != m_listObserver.end();it++){
        (*it)->Update(this);
    }
}

void Subject::Attach(Observer *pObserver)
{
    cout << "Attach an Observer" << endl;
    m_listObserver.push_back(pObserver);
}

void Subject::Dettach(Observer *pObserver)
{
    list<Observer*>::iterator it;
    it = find(m_listObserver.begin(),m_listObserver.end(),pObserver);
    if(it != m_listObserver.end()){
        m_listObserver.erase(it);
    }
    cout << "Detach an Observer" << endl;
}

void Subject::setState(int state)
{
    cout << "SetState By Subject" << endl;
    m_subjectState = state;
}

int Subject::getState()
{
    cout << "GetState By Subject" << endl;
    return m_subjectState;
}


void ConcreateSubject::setState(int state)
{
    cout << "SetState By ConcreateSubject" << endl;
    m_subjectState = state;
}

int ConcreateSubject::getState()
{
    cout << "GetState By ConcreateSubject" <<endl;
    return m_subjectState;
}


void ConcreateObserver::Update(Subject *pSubject)
{
    if(pSubject == NULL){
        return ;
    }
    m_observerState = pSubject->getState();
    cout << "The ObeserverState is " << m_observerState << endl;
}
