#include <iostream>
#include <cstring>
using namespace std;
/**
 * 模板适合于实现一些独立于类型的通用算法，
 * 比如求最大值，排序，查找,拆分，合并,交换，赋值,拷贝。
 */
//通用版本
template<typename T>
class Comparator{
public:
    Comparator(T x,T y):m_x(x),m_y(y){}
    T max(void) const {
        return m_x > m_y ? m_x:m_y;
    }
private:
    T m_x;
    T m_y;
};
//针对const char*的全类特化版本
#if 0
template<>
class Comparator<const char*>{
public:
    Comparator(const char* x,const char* y):m_x(x),m_y(y){
        
    }
    const char* max(void)const{
        return strcmp(m_x,m_y)>0 ? m_x : m_y;
    }
private:
    const char *m_x;
    const char *m_y;
};
#endif
//针对const char*的成员特化版本,除了这个特化的成员函数,其他的还是用通用的版本
template<>
const char* Comparator<const char*>::max(void) const {
    return strcmp(m_x,m_y) > 0 ? m_x : m_y;
}

int main(void){
    /**
     * Comparator是一个模板，模板不能实例化对象
     * Comparator<int>这才是一个类，
     * 函数模板可以隐式推断，但是类模板不可以隐式推断
     * 因为类的构造函数是可以重载的，可以有好几个版本，
     * 所以没有办法隐式推断
     */
    //编译器在编译这句话的时候会生成一个int版的类
    Comparator<int> c1(100,200);
    cout << c1.max() << endl;
    //生成一个string版的类
    Comparator<string> c2("hello","world");
    cout << c2.max() << endl;
    //生成一个double版的类
    Comparator<double> c3(3.14,5.66);
    cout << c3.max() << endl;
    Comparator<const char*> c4("hello","world");
    cout << c4.max() << endl;
    return  0;
}
