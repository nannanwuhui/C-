#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    union {
        int n;
        char c[4];
    };
    n = 0x12345678;
    printf("%x,%x,%x,%x\n",c[0],c[1],c[2],c[3]);
    return 0;
}
