#include "factory.h"
#include <iostream>
using namespace std;
int main(){
    Creator *p = new ConcreateCreator();
    p->AnOperation();
    delete p;
    std::cin.get();
    return 0;
}
