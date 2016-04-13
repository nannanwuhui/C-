#include <iostream>
using namespace std;
/**
 * 宏函数或者参数宏
 * 宏没有类型的约束
 * 预处理器做替换
 */
#define max(x,y) ((x) > (y) ? (x) : (y))
int main(void){
    cout << max(100,200) << endl;
    /**
     * 没有类型转换，比较的不是"hello"与"world"字符串的大小
     * 而是两个字符串字面值地址的大小
     * 这就是去掉类型所带来的风险,没有类型检查也没有类型转换
     * 宏可以去掉类型限定，但是却会带来像这样的风险
     */
    cout << max("hello","world") << endl;
    return 0;
}


