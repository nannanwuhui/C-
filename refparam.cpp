#include <iostream>
using namespace std;
struct S{
    int arr[5];
};
void foo(int arr[],int size)
{
    for(int i = 0;i < size;i++)
    {
        cout << arr[i] << " ";
        cout<<endl;
    }
}
/**
 *如果要给形参传递一个结构体，这个时候开销会比较大，
 *可以考虑使用引用（使用引用效率会比较高），这个时候如果不想修改这个结构体本身的话，可以使用常引用。
 */
void bar(const S& s){
    //s.arr[0] = 100;//在这里修改s的内容，编译器会报错
}

int main(){
    int arr[] = {1,2,3,4,5};
    foo(arr,sizeof(arr)/sizeof(arr[0]));
    S s;
    bar(s);
    return 0;
}
#if 0
第二课：
１、引用与函数
１）引用型参数
通过引用型参数可以提高参数传递的效率，但是会带来风险，可能会在函数中意外地修改实参的值，为此可以采用const型引用，避免发生这样的错误。
#endif
