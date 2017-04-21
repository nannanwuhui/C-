#include <boost/bind.hpp>
#include <tea/tea.h>
void F2(int i,float f){
    Debug("i:%d,f:%f",i,f);
}
class MyClass{
public:
    void F3(int i,float f){
        Debug("i:%d,f:%f",i,f);
    }
};
int main()
{
    boost::bind(&F2,42,3.14f)();
    MyClass c;
    boost::bind(&MyClass::F3,&c,42,3.14f)();
    return 0;
}

