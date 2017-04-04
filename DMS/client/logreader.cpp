//实现日志读取器类
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>//流控制符
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <arpa/inet.h>
using namespace std;
#include "logreader.h"

LogReader::LogReader(const string &logFile, const string &loginsFile)
    :m_logFile(logFile),m_loginsFile(loginsFile)
{

}

list<MLogRec> &LogReader::readLog() throw (ReadException)
{
    cout << "读取日志开始..." << endl;
    try{
        //备份日志文件
        backup();
        //读取登入文件
        readLoginsFile();
        //读取备份文件
        readBackupFile();
        //匹配登入登出
        match();
        //保存登入文件
        saveLoginsFile();
    }
    catch(BackupException& ex){
        throw ReadException("备份错误");
    }
    catch(ReadException& ex){
        throw ReadException("读取错误");
    }
    catch(SaveException& ex){
        throw ReadException("保存错误");
    }
    catch(...){
        throw ReadException("未知错误");
    }
    cout << "读取日志完成。" << endl;
    return m_logs;
}

void LogReader::backup() throw (BackupException)
{
    cout << "备份日志文件开始..." << endl;
    /**
      * 可以先读，然后往另外一个文件里写，然后再把原来的文件清空。
      * 可以用标c,uc,c++的API都是可以的，但是这里可以用一种更简单的方法。
      * 就是我直接用shell,shell已经具备了文件拷贝的功能。就是我写一个shell脚本，
      * 把我想干的事情都给他干了。然后直接去执行这个shell脚本。
      * 这样会有一个好处，如果说以后你的备份方式改变了，你只要改脚本就可以了。代码不用改了。
      * 但是如果有一天，你的备份方式用户不接受了，你就得改程序。
      */
    //生成备份文件名
    time_t now = time(NULL);
    tm* local = localtime(&now);
    ostringstream oss;
    //setfill('0')缺省的用0填充
    //这个和用sprintf的效果一样，只不过我们用的是c++的风格。
    //用sprintf的时候需要算一下缓冲区多大才够用。不然会溢出。
    //用字符串流的好处是缓冲区会动态的分配，你不需要关心内存需要多大
    //所以拿到的内存总是刚刚好，既不浪费，也不溢出。
    oss << m_logFile << '.' << setfill('0')
        << setw(4) << local->tm_year + 1900
        << setw(2) << local->tm_mon + 1
        << setw(2) << local->tm_mday
        << setw(2) << local->tm_hour
        << setw(2) << local->tm_min
        << setw(2) << local->tm_sec;
    m_backupFile = oss.str();
    //生成备份指令
    string cmd = "./backup.sh ";
    cmd += m_logFile;
    cmd += " ";
    cmd += m_backupFile;
#ifdef _DEBUG
    cout << "备份指令:" << cmd << endl;
#endif
    //执行备份指令
    int status = system(cmd.c_str());
    //怎么从返回值中拿到shell执行的退出码呢？
    //拿到退出码，任何一个进程结束以后，那个waitpid返回的那个值，拿出退出码就用
    //ＷEXITSTATUS宏
    if(WEXITSTATUS(status) == 1){
        throw BackupException("拷贝错误");
    }
    if(WEXITSTATUS(status) == 2){
        throw BackupException("清空错误");
    }
    cout << "备份日志文件完成。" << endl;
}

void LogReader::readLoginsFile() throw (ReadException)
{
    cout << "读取登入文件开始..." << endl;
    ifstream ifs(m_loginsFile.c_str(),ios::binary);
    if(ifs){
        LogRec log;
        //ifs读到的字节数如果和你给出的第二个参数相等，就会返回true
        //读到的字节数小于给出的第二个参数的时候，就会返回false
        //返回的是ifs对象本身，他可以隐式的转换成bool类型
        while (ifs.read((char*)&log,sizeof(log))) {
            m_logins.push_back(log);
        }
        //返回false有两种情况，要么是出错，要么是遇到文件尾（ifs.eof返回true）
        if(!ifs.eof()){
            throw ReadException();
        }
        ifs.close();
        unlink(m_loginsFile.c_str());
    }
#ifdef _DEBUG
    cout << "登入日志记录:" << m_logins.size() << endl;
#endif //_DEBUG
    cout << "读取登入文件完成。" << endl;
}

void LogReader::readBackupFile() throw (ReadException)
{
    cout << "读取备份文件开始..." << endl;
    //.开头的可以直接丢掉，因为如果你的用户名登录的是.开头的，一般都是伪用户
    //不是实际用户，往往是伪终端，终端软件比如像telnet,ssh,终端软件生成的一个
    //伪用户名，不是实际用户名
    //读文件，标c,uc，c++都可以

    //打开备份文件
    //在Unix下后面的ios::binary给不给都一样，但是如果这个程序要移植到
    //苹果平台上去，它的行尾符和我们unix的行尾符不一样，unix行尾符是\n,
    //苹果的内核虽然是BSD的，也是unix,但是它的行尾符是回车，不一样
    //为了避免行尾符的转换，所以加上了binary,用统一的模式来处理
    ifstream ifs(m_backupFile.c_str(),ios::binary);
    if(!ifs){
        throw ReadException("备份文件无法打开");
    }
    //计算记录条数
    struct stat st;
    if(stat(m_backupFile.c_str(),&st) == -1){
        throw ReadException("无法获取备份文件大小");
    }
    int records = st.st_size / 372;
    //逐条读取记录
    for(int i = 0;i < records;++i){
        ifs.seekg(i * 372,ios::beg);//定位到记录头
        char logname[32];
        ifs.read(logname,32);//32个字节包含'\0';
        //登录进程ID
        ifs.seekg(36,ios::cur);
        pid_t pid;
        ifs.read((char*)&pid,sizeof(pid));
        pid = ntohl(pid);//网络字节序转主机字节序
        //登录类型：7登入/8登出
        short type;
        ifs.read((char*)&type,sizeof(type));
        type = ntohs(type);
        //登入登出时间
        ifs.seekg(6,ios::cur);
        long logtime;
        ifs.read((char*)&logtime,sizeof(logtime));
        logtime = ntohl(logtime);
        //登录IP长度
        ifs.seekg(28,ios::cur);
        short len;
        ifs.read((char*)&len,sizeof(len));
        len = ntohs(len);
        //登录IP或者机器名
        char logip[len+1];
        ifs.read(logip,len);
        logip[len] = '\0';
#ifdef _DEBUG
        cout << logname << ','
             << pid << ','
             << type << ','
             << logtime << ','
             << len << ','
             << logip << endl;
#endif
        if(logname[0] != '.'){
            LogRec log;
            strcpy(log.logname,logname);
            strcpy(log.logip,logip);
            log.pid = pid;
            log.logtime = logtime;
            if(type == 7){
                m_logins.push_back(log);
            }
            else
            if(type == 8){
                m_logouts.push_back(log);
            }
        }
    }
    ifs.close();
    cout << "登入日志记录:" << m_logins.size() << endl;
    cout << "登出日志记录：" << m_logouts.size() << endl;
    cout << "读取备份文件完成。" << endl;
}

void LogReader::match()
{
    cout << "匹配登入登出开始..." << endl;
    //迭代器是一个内部类
    typedef list<LogRec>::iterator IT;
    //对登出日志记录集中的每一条记录...
    //m_logouts.end()返回的是最后一个元素的下一个迭代器
    for(IT oit = m_logouts.begin();oit != m_logouts.end();++oit){
        //在登入日志记录集中查找匹配记录...
        for(IT iit = m_logins.begin();iit != m_logins.end();++iit){
            if(!strcmp(iit->logname,oit->logname)//登录名一致
                    && !strcmp(iit->logip,oit->logip)//登录IP一致
                    && iit->pid == oit->pid){//PID一致
                    MLogRec log = {"","",0,0,0,0};
                    strcpy(log.logname,oit->logname);
                    strcpy(log.logip,oit->logip);
                    log.pid = oit->pid;
                    log.logintime = iit->logtime;
                    log.logouttime = oit->logtime;
                    log.durations = log.logouttime - log.logintime;
                    m_logs.push_back(log);
                    //从登入日志记录集中删除与登出日志记录匹配的记录
                    //剩下的都是没有登出日志记录与之匹配的登入日志记录
                    m_logins.erase(iit);
                    break;
            }
        }
    }
#ifdef _DEBUG
    cout << "匹配日志记录:" << m_logs.size() << endl;
#endif//_DEBUG
    cout << "匹配登入登出完成。" << endl;
}

void LogReader::saveLoginsFile() throw (SaveException)
{
    cout << "保存登入文件开始..." << endl;
    if(!m_logins.empty()){
        //打开输出文件
        ofstream ofs(m_loginsFile.c_str(),ios::binary);
        if(!ofs)
            throw SaveException();
        while(!m_logins.empty()){
            //m_logins.front()返回的是一个引用，而ofs.write的第一个参数
            //是内存缓冲区的指针
            ofs.write((char*)&m_logins.front(),sizeof(LogRec));
            m_logins.pop_front();
        }
        ofs.close();
    }
    cout << "保存登入文件完成。" << endl;
}
