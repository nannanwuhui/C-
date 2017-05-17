#ifndef SINGLETON_H
#define SINGLETON_H
class Singleton{
public:
    Singleton(){}
    virtual ~Singleton(){}
    // 静态成员函数,提供全局访问的接口
    static Singleton* GetInstancePtr();
    static Singleton GetInstance();
    void Test();
private:
    // 静态成员变量,提供全局惟一的一个实例
    static Singleton* m_pStatic;
};
#endif // SINGLETON_H

