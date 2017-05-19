#include "flyweight.h"


int main()
{
    FlyweightFactory flyweightfactory;
    flyweightfactory.GetFlyweight("hello");
    flyweightfactory.GetFlyweight("world");
    flyweightfactory.GetFlyweight("hello");
    flyweightfactory.GetFlyweight("world");

    cin.get();
    return 0;
}

