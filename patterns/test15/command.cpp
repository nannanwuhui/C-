#include "command.h"
#include <iostream>

using namespace std;


void Receiver::Action()
{
    cout << "Receiver Action" << endl;
}


Invoker::~Invoker()
{
    delete m_pCommand;
    m_pCommand = NULL;
}

void Invoker::Invoke()
{
    if(m_pCommand != NULL){
        m_pCommand->Execute();
    }
}


ConcreateCommand::~ConcreateCommand()
{
    delete m_pReceiver;
    m_pReceiver = NULL;
}

void ConcreateCommand::Execute()
{
    if(m_pReceiver != NULL){
        m_pReceiver->Action();
    }
    cout << "Execute by ConcreateComand" << endl;
}
