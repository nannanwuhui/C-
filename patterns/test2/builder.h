#ifndef BUILDER_H
#define BUILDER_H
// 虚拟基类,是所有 Builder 的基类,提供不同部分的构建接口函数
class Builder{
public:
    Builder(){}
    virtual ~Builder(){}
    // 纯虚函数,提供构建不同部分的构建接口函数
    virtual void BuilderPartA() = 0;
    virtual void BuilderPartB() = 0;
};
// 使用 Builder 构建产品,构建产品的过程都一致,但是不同的 builder 有不同的实现
// 这个不同的实现通过不同的 Builder 派生类来实现,存有一个 Builder 的指针,通过这个来实现多态调用
class Director{
public:
    Director(Builder *pBuilder);
    virtual ~Director();
    void Construct();
private:
    Builder *m_pBuilder;
};
// Builder 的派生类,实现 BuilderPartA 和 BuilderPartB 接口函数
class ConcreateBuilder1 : public Builder{
public:
    ConcreateBuilder1(){}
    virtual ~ConcreateBuilder1(){}
    virtual void BuilderPartA();
    virtual void BuilderPartB();
};
// Builder 的派生类,实现 BuilderPartA 和 BuilderPartB 接口函数
class ConcreateBuilder2 : public Builder{
public:
    ConcreateBuilder2(){}
    virtual ~ConcreateBuilder2(){}
    virtual void BuilderPartA();
    virtual void BuilderPartB();
};

#endif // BUILDER_H

