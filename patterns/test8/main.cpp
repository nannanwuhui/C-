#include <iostream>
#include "bridge.h"

using namespace std;

int main()
{
    ConcreateImplementorA *pImplA = new ConcreateImplementorA;
    Abstraction *pAbstraction1 = new Abstraction(pImplA);
    pAbstraction1->Operation();

    ConcreateImplementorB *pImplB = new ConcreateImplementorB;
    Abstraction *pAbstraction2 = new Abstraction(pImplB);
    pAbstraction2->Operation();

    delete pAbstraction1;
    delete pAbstraction2;
    return 0;
}

