#include <iostream>
#include <cstdio>
/*
class MyClass{
public:
    int i;
    int ii;
    int iii;//why not 16?
};
*/
class MyClass{
public:
    char a;
    int b;
};
int main(void)
{
    printf("%lu,%lu\n",sizeof(size_t),sizeof(MyClass));//8,8
    return 0;
}
