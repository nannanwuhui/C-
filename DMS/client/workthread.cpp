//实现工作线程类
#include "workthread.h"
#include "logreader.h"
#include "socketsender.h"
#include "client.h"

void WorkThread::run()
{
#if 0
    emit(update("Hello,World!"));
    sleep(1);
    emit(update("Hello,World!"));
    sleep(1);
    emit(update("Hello,World!"));
    sleep(1);
    emit(update("Hello,World!"));
    sleep(1);
    emit(update("Hello,World!"));
#endif
    try{
        LogReader reader("./wtmpx","./logins.dat");
//            ConsoleSender sender;
        //127.0.0.1是在协议栈里转了一圈，只不过是不走驱动，不走网卡（不进链路层，只进协议层）
        SocketSender sender("127.0.0.1",8888,"./fail.dat",this);
        Client client(reader,sender);
        client.dataMine();
    }
    catch(exception& ex){
        cout << ex.what() << endl;
    }
}

void WorkThread::update(const string &text)
{
    emit(update(QString(text.c_str())));
}

