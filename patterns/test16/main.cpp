#include "observer.h"


int main()
{
    Observer *pObserver1 = new ConcreateObserver;
    Observer *pObserver2 = new ConcreateObserver;

    Subject *pSubject = new ConcreateSubject;
    pSubject->Attach(pObserver1);
    pSubject->Attach(pObserver2);

    pSubject->setState(4);
    pSubject->Notify();

    cout << "*******************" << endl;
    pSubject->Dettach(pObserver1);
    pSubject->setState(10);
    pSubject->Notify();

    delete pSubject;
    cin.get();
    return 0;
}

