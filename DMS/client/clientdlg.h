//声明客户机对话框类
#ifndef _CLIENTDLG_H
#define _CLIENTDLG_H
#include <QDialog>
#include "workthread.h"
class QTextBrowser;//短式声明，前置声明
class ClientDlg : public QDialog{
    Q_OBJECT //为了让槽函数正确的扩展
public:
    ClientDlg();
public slots:
    void onStart();
    void onUpdate(QString text);
private:
    QTextBrowser* m_browser;
    WorkThread m_work;
};
#endif //_CLIENTDLG_H
