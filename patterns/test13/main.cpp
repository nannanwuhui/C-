#include "chainofresponsibility.h"

using namespace std;

int main()
{
    Handler *p1 = new ConcreateHandler1();
    Handler *p2 = new ConcreateHandler2(p1);

    p2->HandleRequest();

    delete p2;
    cin.get();
    return 0;
}

