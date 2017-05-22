#include "state.h"
#include <iostream>

using namespace std;

Context::Context(State* pState)
: m_pState(pState)
{
}

Context::~Context()
{
    delete m_pState;
    m_pState = NULL;
}

void Context::request()
{
    if(m_pState != NULL){
        m_pState->Handle(this);
    }
}

void Context::changeState(State *pState)
{
    if(m_pState != NULL){
        delete m_pState;
        m_pState = NULL;
    }
    m_pState = pState;
}



void ConcreateStateA::Handle(Context *pContext)
{
    cout << "Handle by ConcreateStateA" << endl;

    if(pContext != NULL){
        pContext->changeState(new ConcreateStateB());
    }
}


void ConcreateStateB::Handle(Context *pContext)
{
    cout << "Handle by ConcreateStateB" << endl;

    if(pContext != NULL){
        pContext->changeState(new ConcreateStateA());
    }
}
