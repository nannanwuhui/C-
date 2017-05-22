#include <iostream>
#include "iterator.h"
using namespace std;

int main()
{
    Aggregate *pAggregate = new ConcreateAggregate(4);
    Iterator *it = new ConcreateIterator(pAggregate);
    for(;false == it->isDone();it->next()){
        cout << it->currentItem() << endl;
    }
    return 0;
}

