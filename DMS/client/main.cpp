#include <QApplication>
#include <iostream>
using namespace std;
#include "logreader.h"
#include "consolesender.h"
#include "socketsender.h"
#include "client.h"
#include "clientdlg.h"
#include <cstring>
//先粗然后再精，先把框架性的东西给搭建起来，先把流程走通，然后再细化
//符合敏捷开发的方式
int main(int argc,char* argv[]){
    if(argc < 2){
        try{
            LogReader reader("./wtmpx","./logins.dat");
//            ConsoleSender sender;
            //127.0.0.1是在协议栈里转了一圈，只不过是不走驱动，不走网卡（不进链路层，只进协议层）
                    SocketSender sender("127.0.0.1",8888,"./fail.dat");
            Client client(reader,sender);
            client.dataMine();
        }
        catch(ClientException& ex){
            cout << ex.what() << endl;
            return -1;
        }
    }
    else if(!strcmp(argv[1],"-g")){
//        cout << "图形界面还没有实现!" << endl;
        QApplication app(argc,argv);
        ClientDlg dlg;
        dlg.show();
        return app.exec();
    }
    else{
        cerr << "用法:" << argv[0] << "[-g]" << endl;
        return -1;
    }
    return 0;
}
