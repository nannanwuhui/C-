#ifndef ITERATOR_H
#define ITERATOR_H
class Iterator;
// 容器的抽象基类
class Aggregate
{
public:
    virtual ~Aggregate(){}
    virtual Iterator* createIterater(Aggregate *pAggregate) = 0;
    virtual int getSize() = 0;
    virtual int getItem(int index) = 0;
};
// 迭代器的抽象基类
class Iterator
{
public:
    virtual ~Iterator(){}

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual int currentItem() = 0;
};
// 一个具体的容器类,这里是用数组表示
class ConcreateAggregate : public Aggregate
{
public:
    ConcreateAggregate(int size);
    virtual ~ConcreateAggregate();

    virtual Iterator* createIterater(Aggregate *pAggregate);
    virtual int getSize();
    virtual int getItem(int index);
private:
    int m_size;
    int *m_pdata;
};
// 访问 ConcreateAggregate 容器类的迭代器类
class ConcreateIterator : public Iterator
{
public:
    ConcreateIterator(Aggregate *pAggregate);
    virtual ~ConcreateIterator(){}

    virtual void first();
    virtual void next();
    virtual bool isDone();
    virtual int currentItem();
private:
    Aggregate *m_pConcreateAggregate;
    int m_index;
};
#endif // ITERATOR_H

