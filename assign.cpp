#include <iostream>
using namespace std;
/*void foo(int a){
    a=100;
}*/
void foo(int *pa){
    *pa = 100;
}
void foo(int& ra){
    cout << "int& ra" << endl;
    ra=100;
}
void bar(char** psz)
{
    *psz="world";
}
void bar(char*& psz)
{
    cout << "char*& psz" << endl;
    psz="world";
}
int main(){
    int a=0;
    foo(a);
    cout << a << endl;
    char *psz="hello";
    bar(psz);
    cout << psz << endl;
    return 0;
}
