#include <iostream>
#include "command.h"
using namespace std;

int main()
{
    Receiver *pReceiver = new Receiver();
    Command *pCommand = new ConcreateCommand(pReceiver);
    Invoker *pInvoker = new Invoker(pCommand);
    pInvoker->Invoke();

    delete pInvoker;
    cin.get();
    return 0;
}

