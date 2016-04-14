#include <iostream>
#include <cstring>
using namespace std;
class Student{
public:
   // Student(const string& strName,int nAge):m_strName(strName),m_nAge(nAge){}
  //  Student(const Student& student):m_strName(student.m_strName),m_nAge(student.m_nAge){}
    Student(const char* pszName,int nAge):m_pszName(NULL),m_nAge(nAge){
        m_pszName = new char[strlen(pszName) + 1];
        strcpy(m_pszName,pszName);
    }
#if 1    
    Student(const Student& student):m_pszName(NULL),m_nAge(student.m_nAge){
        m_pszName = new char[strlen(student.m_pszName) + 1];
        strcpy(m_pszName,student.m_pszName);
    }
#endif
    ~Student(void){
        delete[] m_pszName;
    }
    void Print(void){
        cout << m_pszName << "," << m_nAge << endl;
    }
private:
    //string m_strName;
    char *m_pszName;
    int m_nAge;
};
int main(){
    Student s1("张飞",28);
    s1.Print();
    /**
     * 这种方式的话，s1里的m_pszName和s2中的m_pszName是一样的，都是地址值，当s1离开作用域的时候
     * 会调用析构函数，当s2离开作用的时候也会调用析构函数，这样的话，就会double
     * free,释放了两次
     */
    Student s2(s1);
    s2.Print();
#if 0
    Student s3 = s2;
    s3.Print();
    Student *ps = new Student(s3);
    ps->Print();
    delete ps;
#endif
    return 0;
}
#if 0
6、拷贝构造函数和拷贝赋值运算符
A a1;
A a2(a1);
A a2 = a1;
这两种形式是等价的。
两个对象的成员变量都是一样的。具有相同的属性。
A *pa2 = new A(a1);指针pa2所指向的A类型的对象和a1里的成员变量是一样的.
如果我们不提供拷贝构造函数，系统会给我们提供一个默认的拷贝构造函数。
如果我们提供了拷贝构造函数，则系统不会再给我们提供。
拷贝构造函数也是一个构造函数。
1）缺省方式的拷贝构造函数就是按字节复制一份和拷贝源一模一样的副本
2）自定义拷贝构造函数
class 类名{
	类名（const 类名& obj）{
	以拷贝的方式从obj复制成员变量的值（当然也可以在初始化表里做复制）
}
};
3）缺省方式的字节复制往往不能实现对象间的深拷贝，这时就需要提供自己定义的拷贝构造函数，以获得真正意义上的副本。如果缺省方式的拷贝构造函数可以完成拷贝的任务，则不需要提供自定义的拷贝构造函数。

拷贝构造可能开销会很大。
#endif
