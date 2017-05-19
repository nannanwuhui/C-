#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H
#include <iostream>
// 抽象基类,定义一个处理请求的接口
class Handler
{
public:
    Handler(Handler *pSuccessor = NULL);
    virtual ~Handler();
    // 纯虚函数,由派生类实现
    virtual void HandleRequest() = 0;
protected:
    Handler *m_pSuccessor;
};

class ConcreateHandler1 : public Handler
{
public:
    ConcreateHandler1(Handler *pSuccessor = NULL) : Handler(pSuccessor){}
    virtual ~ConcreateHandler1(){}
    virtual void HandleRequest();
};

class ConcreateHandler2 : public Handler
{
public:
    ConcreateHandler2(Handler *pSuccessor = NULL) : Handler(pSuccessor){}
    virtual ~ConcreateHandler2(){}
    virtual void HandleRequest();
};
#endif // CHAINOFRESPONSIBILITY_H

