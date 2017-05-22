#include <iostream>
#include "strategy.h"

using namespace std;

int main()
{
    Strategy *pStrategy = new ConcreateStrategyA();
    Context *pContext = new Context(pStrategy);

    pContext->ContextInterface();
    delete pContext;
    return 0;
}

