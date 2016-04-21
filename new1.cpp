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
    //p = new int[10]={10,20,30};//这种初始化的方法是不对的。new int[10]出来的仅仅是一块内存的首地址
    //int a[5]={1,2,3,4,5};//c里面这种方法是对的
    //delete[] p;//如果不加[]进行释放，只会释放第一个int,后面９个不释放。
    p = NULL;
    return 0;
}
