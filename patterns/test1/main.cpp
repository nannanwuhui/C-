#include "abstractfactory.h"
#include <iostream>
using namespace std;
int main(){
    //生产产品A的第一种实现
//    ConcreateFactory1 *pFactory1 = new ConcreateFactory1;
    AbstractFactory *pFactory1 = new ConcreateFactory1;
    AbstractProductA *pProductA = pFactory1->CreateProductA();
    //生产产品B的第二种实现
//    ConcreateFactory2 *pFactory2 = new ConcreateFactory2;
    AbstractFactory *pFactory2 = new ConcreateFactory2;
    AbstractProductB *pProductB = pFactory2->CreateProductB();

    delete pFactory1;
    delete pProductA;
    delete pFactory2;
    delete pProductB;
    return 0;
}
