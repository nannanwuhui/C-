#include <iostream>
using namespace std;
/**
 * 预处理器做宏扩展
 */
#define MAX(T) \
T max_##T(T x,T y){ \
    return x > y ? x : y; \
}
/**
 * 这其实就是两个函数的定义
 * 与其让预处理器做文本替换 
 * 还不如让更聪明的编译器来做这件事(安全性的检查,语法检查,功能比预处理器强大)
 * 这样，功能，可操作性，灵活性上会更好
 */
MAX(int)
MAX(string)
MAX(double)
#define max(T) max_##T
int main(void){
    cout << max(int)(100,200) << endl;
    cout << max(string)("hello","world") << endl;
    cout << max(double)(3.14,5.66) << endl; 
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/121915$ g++ -E max3.cpp -o max3.i
zn@zn-OptiPlex-9010:~/demo/121915$ gvim max3.i 
然后跳到最后一行，你就可以看到预编译之后的结果。
#endif
