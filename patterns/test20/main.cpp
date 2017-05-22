#include "memento.h"


int main()
{
    // 创建一个原发器
    Originator *pOriginator = new Originator("old state");
    pOriginator->printState();
    // 创建一个备忘录存放这个原发器的状态
    Memento *pMemento = pOriginator->createMemento();
    // 更改原发器的状态
    pOriginator->setState("new State");
    pOriginator->printState();
    // 通过备忘录把原发器的状态还原到之前的状态
    pOriginator->restoreState(pMemento);
    pOriginator->printState();

    delete pOriginator;
    delete pMemento;
    return 0;
}

