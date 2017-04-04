//声明工作线程类
#ifndef _WORKTHREAD_H
#define _WORKTHREAD_H
#include <QThread>
#include <QString>
#include <string>
using namespace std;
class WorkThread : public QThread{
    Q_OBJECT
public:
    void run();
    void update(const string& text);
signals:
    void update(QString text);//信号函数不需要自己实现，槽函数需要自己实现
};
#endif//_WORKTHREAD_H
