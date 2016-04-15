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
#if 0
２）联合(和结构体，除关键字不一样，)
union UN{
	int n;
	char c[4];
};
A.使用联合定义变量可以省略union关键字
B.不定义变量，直接访问联合的成员

zn@zn-OptiPlex-9010:~/demo/102015$ g++ union.cpp 
zn@zn-OptiPlex-9010:~/demo/102015$ ./a.out 
78,56,34,12
#endif
