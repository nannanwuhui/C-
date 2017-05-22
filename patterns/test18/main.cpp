#include <iostream>
#include "state.h"
using namespace std;

int main()
{
    State *pState = new ConcreateStateA();
    Context *pContext = new Context(pState);
    pContext->request();
    pContext->request();
    pContext->request();

    delete pContext;
    return 0;
}

