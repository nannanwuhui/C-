#ifndef FACTORY_H
#define FACTORY_H
//除了构造和析构之外 如果所有的函数都是纯虚函数则这个类叫纯抽象类
//纯抽象类
class Product{
public:
    Product();
    virtual ~Product();
};
//纯抽象类
class ConcreateProduct : public Product{
public:
    ConcreateProduct();
    virtual ~ConcreateProduct();
};
class Creator{
public:
    Creator();
    virtual ~Creator();
    void AnOperation();
protected:
    virtual Product* FactoryMethod()=0;
};
class ConcreateCreator:public Creator{
public:
    ConcreateCreator();
    virtual ~ConcreateCreator();
protected:
    virtual Product* FactoryMethod();
};
#endif // FACTORY_H

