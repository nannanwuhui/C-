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
    void SpecialRequest();
};
class Adapter : public Target
{
public:
    Adapter(Adaptee *pAdaptee);
    virtual ~Adapter();
    virtual void Request();
private:
    Adaptee *m_pAdaptee;
};
#endif // ADAPT_H

