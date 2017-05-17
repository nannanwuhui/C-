#ifndef PROTOTYPE_H
#define PROTOTYPE_H

// 虚拟基类,所有原型的基类,提供 Clone 接口函数
//纯抽象类
class Prototype
{
public:
    Prototype() {}
    virtual ~Prototype(){}

    virtual Prototype* Clone() = 0;
};
// 派生自 Prototype,实现 Clone 方法
class ConcreatePrototype1 : public Prototype
{
public:
    ConcreatePrototype1();
    ConcreatePrototype1(const ConcreatePrototype1& other);
    virtual ~ConcreatePrototype1();

    virtual Prototype* Clone();
};

// 派生自 Prototype,实现 Clone 方法
class ConcreatePrototype2 : public Prototype
{
public:
    ConcreatePrototype2();
    ConcreatePrototype2(const ConcreatePrototype2& other);
    virtual ~ConcreatePrototype2();

    virtual Prototype* Clone();
};
#endif // PROTOTYPE_H

