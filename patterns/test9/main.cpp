#include <iostream>
#include "composite.h"
using namespace std;

int main()
{
    Leaf *pLeaf1 = new Leaf();
    Leaf *pLeaf2 = new Leaf();
    Composite *pComposite = new Composite;
    pComposite->Add(pLeaf1);
    pComposite->Add(pLeaf2);
    pComposite->Operation();
    cout << "pComposite->GetChild(2)->Operation():" << endl;
    pComposite->GetChild(2)->Operation();
    delete pComposite;
    cin.get();
    return 0;
}

