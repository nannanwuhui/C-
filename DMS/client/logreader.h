//声明日志读取器类
#ifndef _LOGREADER_H
#define _LOGREADER_H
#include <string>
#include <list>
using namespace std;
#include "data.h"
#include "except.h"
//日志读取器类
class LogReader{
public:
    //构造器
    LogReader(const string& logFile,const string& loginsFile);
    //读取日志,返回引用，避免内存拷贝的开销
    list<MLogRec>& readLog() throw (ReadException);
private:
    //备份日志文件
    void backup() throw (BackupException);
    //读取登入文件
    void readLoginsFile() throw (ReadException);
    //读取备份文件
    void readBackupFile() throw (ReadException);
    //匹配登入登出
    void match();
    //保存登入文件
    void saveLoginsFile() throw (SaveException);
    string m_logFile;//日志文件，前置条件
    string m_loginsFile;//登入文件,前置条件
    string m_backupFile;//备份文件，根据时间规则自己生成的
    list<LogRec> m_logins;//登入日志记录集
    list<LogRec> m_logouts;//登出日志记录集
    list<MLogRec> m_logs;//匹配日志记录集
};
#endif//_LOGREADER_H
