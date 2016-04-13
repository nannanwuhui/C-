#include <iostream>
#include <cstdlib>
using namespace std;
int main(){
    int *p = (int *)malloc(sizeof(int));
    *p = 100;
    cout<< *p << endl;
    free(p);
    p = NULL;
    p = new int(100);
    cout << *p << endl;
    delete p;
    p = NULL;
    p = new int[10];
    delete[] p;//如果不加[]进行释放，只会释放第一个int,后面９个不释放。
    p = NULL;
    int& r=*new int(200);
    cout << r << endl;
    delete &r;
   // r = 300;//这里不能再用了，但是编译器不会报错。
    int (*pa)[4] = new int[3][4];
    for(int i=0;i<3;i++)
        for(int j=0;j<4;j++)
            cout << pa[i][j] << endl;//缺省初始化都是0
    int (*ppa)[4][5] = new int[3][4][5];//ppa仍然是一个行指针，只不过是一个二维行
    delete[] ppa;//不加[],只delete ppa所指向的那一个元素
    return 0;
}
#if 0
９、C++的内存分配
int *p;
int a[10];
int *p[10];
int (*p)[10];数组指针，首先p是一个指针，它指向一个１０个int组成的数组。
int *p(); 这是一个函数，函数不带参数，返回值是int*
int (*p)();这是一个函数指针，指向不带参数，返回值是int的函数。
int **p;
new（运算符和加减乘除一样）／delete
new虽然最后也是调用malloc来实现内存分配的，但是在执行malloc之前做了一些事情，所以不能用new分配内存，然后使用free来释放内存，这样只是做了malloc对应的部分，前面的部分没有做
malloc(标准库函数)和printf一样
１、new不需要知道分配内存的大小，只需要知道类型就可以了。
２、new在分配内存的时候就可以初始化，但是malloc只能在分配好内存以后进行初始化。
３、new在分配内存时不需要进行类型转换，而malloc分配的内存都是void *,需要进行类型转换。
４、new除了分配内存还会调用构造函数。
new 类型（要初始化的值），返回的是 类型*
#endif

