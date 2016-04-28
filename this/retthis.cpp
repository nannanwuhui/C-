#include <iostream>
using namespace std;
class Counter{
public:
    Counter(int cn = 0):m_cn(cn){
    
    
    }
    /*
    Counter& Inc(void){
        m_cn++;
        return *this;
    }
    Counter& Dec(){
        m_cn--;
        return *this;
    }
    */
    Counter Inc(void){
        m_cn++;
        return *this;
    }
    Counter Dec(){
        m_cn--;
        return *this;
    }
    void Print(){
        cout << m_cn << endl;
    }
private:
    int m_cn;
};
int main(){
    Counter counter;
    /*
    counter.Inc();
    counter.Inc();
    counter.Inc();
    counter.Dec();
    */
    /**
     * Inc(),Dec()返回的如果不是引用，而是Counter的话，返回的只是一个副本，所以
     * counter.Print();打印出来的是1.
     * 这样的累加只是在副本里做累加，不是在一个变量里做累加
     * 只有当返回引用的时候，才可以始终在一个变量里做累加
     */
    counter.Inc().Inc().Inc().Dec().Print();
    counter.Print();
    return 0;

}
#if 0
3）this指针可以用于返回自引用的场合
返回自己和返回自己的拷贝是不一样的。
#endif
