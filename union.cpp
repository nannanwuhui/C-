#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    union {
        int n;
        char c[4];
    } un;
    un.n = 0x12345678;
    printf("%x,%x,%x,%x\n",un.c[0],un.c[1],un.c[2],un.c[3]);
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/102015$ g++ union.cpp 
zn@zn-OptiPlex-9010:~/demo/102015$ ./a.out 
78,56,34,12(小端序，低位放低地址，高位放高地址)
以上是c的写法，因为c++可以兼容c，所以这样写当然是可以的。
#endif
