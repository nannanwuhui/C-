#include "chainofresponsibility.h"



Handler::Handler(Handler *pSuccessor)
    :m_pSuccessor(pSuccessor)
{

}

Handler::~Handler()
{
    delete m_pSuccessor;
    m_pSuccessor = NULL;
}


void ConcreateHandler1::HandleRequest()
{
    if(m_pSuccessor != NULL){
        m_pSuccessor->HandleRequest();
    }
    else{
        std::cout << "HandleRequset by ConcreateHandler1" << std::endl;
    }
}


void ConcreateHandler2::HandleRequest()
{
    if(m_pSuccessor != NULL){
        m_pSuccessor->HandleRequest();
    }
    else{
        std::cout << "HandleRequset by ConcreateHandler2" << std::endl;
    }
}
