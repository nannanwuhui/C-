#include <iostream>

using namespace std;
template<typename T>
class Singleton{
public:
    Singleton(){}
    virtual ~Singleton(){}
    static T* GetInstancePrt(){
        if(NULL == m_pStatic){
            m_pStatic = new T;
        }
        return m_pStatic;
    }
    static T GetInstance(){
        return *GetInstancePrt();
    }
private:
    // 静态成员变量,提供全局惟一的一个实例
    static T* m_pStatic;
};
template<typename T>
T* Singleton<T>::m_pStatic = NULL;

class Test/* : public Singleton<Test>*/
{
public:
    void test(){
        cout << "**** Test *****" << endl;
    }
};
int main()
{
    Singleton<Test>::GetInstancePrt()->test();
    Singleton<Test>::GetInstance().test();
    return 0;
}

