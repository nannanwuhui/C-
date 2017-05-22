#ifndef STATE_H
#define STATE_H
class State;
class Context
{
public:
    Context(State *pState);
    ~Context();
    void request();
    void changeState(State *pState);
private:
    State *m_pState;
};

class State
{
public:
    virtual ~State(){}
    virtual void Handle(Context *pContext) = 0;
};

class ConcreateStateA : public State
{
public:
    virtual void Handle(Context *pContext);
};

class ConcreateStateB : public State
{
public:
    virtual void Handle(Context *pContext);
};
#endif // STATE_H

