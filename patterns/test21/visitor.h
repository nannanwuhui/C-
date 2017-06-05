#ifndef VISITOR_H
#define VISITOR_H
class Visitor;
class Element
{
public:
    virtual ~Element(){}
    virtual void accept(Visitor& visitor) = 0;
protected:
    Element(){}
};

class ConcreateElementA : public Element
{
public:
    virtual ~ConcreateElementA(){}
    virtual void accept(Visitor& visitor);
};

class ConcreateElementB : public Element
{
public:
    virtual ~ConcreateElementB(){}
    virtual void accept(Visitor& visitor);
};

class Visitor
{
public:
    virtual ~Visitor(){}
    virtual void visitConcreateElementA(ConcreateElementA *pConcreateElementA) = 0;
    virtual void visitConcreateElementB(ConcreateElementB *pConcreateElementB) = 0;
protected:
    Visitor(){}
};

class ConcreateVisitorA : public Visitor
{
public:
    virtual ~ConcreateVisitorA(){}
    virtual void visitConcreateElementA(ConcreateElementA *pConcreateElementA);
    virtual void visitConcreateElementB(ConcreateElementB *pConcreateElementB);
};

class ConcreateVisitorB : public Visitor
{
public:
    virtual ~ConcreateVisitorB(){}
    virtual void visitConcreateElementA(ConcreateElementA *pConcreateElementA);
    virtual void visitConcreateElementB(ConcreateElementB *pConcreateElementB);
};
#endif // VISITOR_H

