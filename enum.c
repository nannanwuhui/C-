#include <stdio.h>
int main(){
    enum E{a,b,c,d};
    //enum E e =100;
    E e = a;//(只能是枚举类型的,不接受整型)
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/102015$ gcc enum.c (没有问题)
zn@zn-OptiPlex-9010:~/demo/102015$ cp enum.c enum.cpp
zn@zn-OptiPlex-9010:~/demo/102015$ g++ enum.cpp
enum.cpp: In function ‘int main()’:
enum.cpp:3:15: error: invalid conversion from ‘int’ to ‘main()::E’ [-fpermissive]
     enum E e =100;
               ^
同样的代码,用c去编译可以通过，但是用c++去编译，c++的编译器就认为类型不一致，
c++把枚举和整型严格的区分了。
#endif
