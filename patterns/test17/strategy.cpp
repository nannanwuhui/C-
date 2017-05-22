#include <iostream>
#include "strategy.h"
using namespace std;


Context::Context(Strategy *pStrategy) : m_pStrategy(pStrategy)
{

}

Context::~Context()
{
    delete m_pStrategy;
    m_pStrategy = NULL;
}

void Context::ContextInterface()
{
    if(m_pStrategy != NULL){
        m_pStrategy->AlgorithmInterface();
    }
}



void ConcreateStrategyA::AlgorithmInterface()
{
    cout << "AlgorithmInterface Implemented by ConcreateStrategyA" << endl;
}
