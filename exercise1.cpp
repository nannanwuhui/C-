#include <iostream>
#include <cstdio>
class MyClass{
public:
    char a;
    double b;
};
int main(void)
{
    printf("%lu,%lu\n",sizeof(size_t),sizeof(MyClass));//8,16
    return 0;
}
