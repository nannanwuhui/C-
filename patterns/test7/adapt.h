#ifndef ADAPT_H
#define ADAPT_H
// 需要被 Adapt 的类
class Target
{
public:
    Target() {}
    virtual ~Target(){}
    virtual void Request() = 0;
};
// 与被 Adapt 对象提供不兼容接口的类
class Adaptee
{
public:
    Adaptee() {}
    ~Adaptee(){}
    virtual void SpecialRequest() = 0;
};
class Adapter : public Target,public Adaptee
{
public:
    Adapter(){}
    virtual ~Adapter(){}
    virtual void Request();
    virtual void SpecialRequest();
};
#endif // ADAPT_H

