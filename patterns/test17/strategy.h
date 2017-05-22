#ifndef STRATEGY_H
#define STRATEGY_H
class Strategy;
class Context
{
public:
    Context(Strategy *pStrategy);
    virtual ~Context();
    void ContextInterface();
private:
    Strategy *m_pStrategy;
};
class Strategy
{
public:
    virtual ~Strategy(){}
    virtual void AlgorithmInterface() = 0;
};
class ConcreateStrategyA : public Strategy
{
    virtual ~ConcreateStrategyA(){}

    virtual void AlgorithmInterface();
};
#endif // STRATEGY_H

