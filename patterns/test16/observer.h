#ifndef OBSERVER_H
#define OBSERVER_H
#include <list>
#include <iostream>
using namespace std;
class Observer;
// Subject 抽象基类,只需要知道 Observer 基类的声明就可以了
class Subject
{
public:
    Subject():m_subjectState(-1){}
    virtual ~Subject();
    void Notify();   // 通知对象改变状态
    void Attach(Observer *pObserver); // 新增对象
    void Dettach(Observer *pObserver); // 删除对象
    // 虚函数,提供默认的实现,派生类可以自己实现来覆盖基类的实现
    virtual void setState(int state);// 设置状态
    virtual int getState();// 得到状态
protected:
    int m_subjectState;// 模拟保存 Subject 状态的变量
    list<Observer*> m_listObserver; // 保存 Observer 指针的链表
};
// Observer 抽象基类
class Observer
{
public:
    Observer():m_observerState(-1){}
    virtual ~Observer(){}
    // 纯虚函数,各个派生类可能有不同的实现
    // 通知 Observer 状态发生了变化
    virtual void Update(Subject* pSubject) = 0;
protected:
    int m_observerState; // 模拟保存 Observer 状态的变量
};
// ConcreateSubject 类,派生在 Subject 类
class ConcreateSubject : public Subject
{
public:
    ConcreateSubject():Subject(){}
    virtual ~ConcreateSubject(){}
    // 派生类自己实现来覆盖基类的实现
    virtual void setState(int state);// 设置状态
    virtual int getState();// 得到状态
};
// ConcreateObserver 类派生自 Observer
class ConcreateObserver : public Observer
{
public:
    ConcreateObserver():Observer(){}
    virtual ~ConcreateObserver(){}
    // 虚函数,实现基类提供的接口
    virtual void Update(Subject *pSubject);
};

#endif // OBSERVER_H

