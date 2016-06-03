#include <iostream>
using namespace std;
class A     
{     
};    
  
class B     
{  
    char ch;     
    virtual void func0()  {  }   
    virtual void func2()  {  }   
    virtual void func4()  {  }   
    void func10()  {  }   
};   
  
class C    
{  
    char ch1;  
    char ch2;  
    virtual void func()  {  }    
    virtual void func1()  {  }   
};  
  
class D: public A,public C   
{     
    int d;     
    virtual void func()  {  }   
    virtual void func1()  {  }  
};     
  
class E: public B, public C  
{     
    int e;     
    virtual void func0()  {  }   
    virtual void func1()  {  }  
};  
  
int main(void)  
{  
    cout<<"sizeof(int):"<<sizeof(int)<<endl;    //result=4  
    cout<<"A="<<sizeof(A)<<endl;    //result=1  
    cout<<"B="<<sizeof(B)<<endl;    //result=16      
    cout<<"C="<<sizeof(C)<<endl;    //result=16  
    cout<<"D="<<sizeof(D)<<endl;    //result=16  
    cout<<"E="<<sizeof(E)<<endl;    //result=32  
    return 0;  
}  
