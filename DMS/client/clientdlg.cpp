//实现客户机对话框类
#include <QtGui>
#include <QObject>
#include "clientdlg.h"
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QPushButton>
#include <unistd.h>
ClientDlg::ClientDlg(){
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    setWindowTitle(tr("DMS数据采集客户机"));
    resize(520,520);
    m_browser = new QTextBrowser(this);
    m_browser->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    QPushButton* btnStart = new QPushButton(tr("开始"),this);
    connect(btnStart,SIGNAL(clicked()),this,SLOT(onStart()));
    QPushButton* btnClose = new QPushButton(tr("关闭"),this);
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));
    QHBoxLayout* layHor = new QHBoxLayout;
    layHor->addStretch();
    layHor->addWidget(btnStart);
    layHor->addWidget(btnClose);
    layHor->addStretch();
    QVBoxLayout* layVer = new QVBoxLayout;
    layVer->addWidget(m_browser);
    layVer->addLayout(layHor);
    setLayout(layVer);
    connect(&m_work,SIGNAL(update(QString)),this,SLOT(onUpdate(QString)));
}

void ClientDlg::onStart()
{
    //在这个槽函数里面执行了5次显示Hello,World的操作，但是每次都只是把
    //Hello,World放到了内存缓冲区里，并没有显示到对话框里，
    //需要等到这个槽函数执行完了，才会将内存缓冲区中的东西更新显示到窗口
    //应该把UI线程和工作线程(业务逻辑)分开，通常UI线程是主线程
    //这两个线程还要交换数据，因为业务逻辑中的数据要在UI中显示，
    //这里我们只要把想要显示在UI中的数据放到append()里就可以了，QT会把
    //我们的数据送给UI线程
#if 0
    m_browser->append("Hello,World!");
    sleep(1);
    m_browser->append("Hello,World!");
    sleep(1);
    m_browser->append("Hello,World!");
    sleep(1);
    m_browser->append("Hello,World!");
    sleep(1);
    m_browser->append("Hello,World!");
#endif
    m_work.start();
}

void ClientDlg::onUpdate(QString text)
{
    //添加以后立刻返回,UI线程就有充分的时间把新添加的东西同步到窗口
    m_browser->append(text);
}
