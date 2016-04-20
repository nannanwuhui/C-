#include <iostream>
using namespace std;
int main(){
    bool b = true;
    cout << b << endl;//1
    b=false;
    cout << b << endl;//0
    cout << sizeof(b) << endl;//1
    b = 3.14;
    cout << b << endl;//1
    b = "hello";
    cout << b << endl;//1
    b = NULL;
    cout << b << endl;//0
    //不能声明引用型数组，引用不占内存空间。
    //int n,m;
    //int& r[2] = {n,m};
    return 0;
}
