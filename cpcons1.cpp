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
    Student(const Student& student):m_pszName(NULL),m_nAge(student.m_nAge){
        cout << "拷贝构造" << endl;
        m_pszName = new char[strlen(student.m_pszName) + 1];
        strcpy(m_pszName,student.m_pszName);
    }
    ~Student(void){
        delete[] m_pszName;
    }
    /**
     * 只有构造函数才能使用初始化表，成员函数不能使用初始化表
     */
    //void operator= (const Student& student){
    /**
     * 默认的拷贝赋值只会做浅拷贝，
     */
    Student& operator= (const Student& student){
        /**
         * 防止自己给自己赋值,和拷贝构造很像，但是要注意三点：
         * 1、赋值之前已经有资源了，要释放掉
         * 2、防止自己给自己赋值
         * 3、返回自引用
         */
        cout << "拷贝赋值" << endl;
        if(&student != this)
        {
            delete[] m_pszName;
            m_pszName = new char[strlen(student.m_pszName) + 1];
            strcpy(m_pszName,student.m_pszName);
            m_nAge = student.m_nAge;
        }
        return *this;//返回调用对象的引用,赋值表达式就会返回左值的引用，这样类类型的赋值表达式就会和简单类型的赋值表达式一样
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
     * 在不提供拷贝构造函数的情况下：
     * 这种方式的话，s1里的m_pszName和s2中的m_pszName是一样的，都是地址值，当s1离开作用域的时候
     * 会调用析构函数，当s2离开作用的时候也会调用析构函数，这样的话，就会double
     * free,释放了两次
     */
    Student s2(s1);
    s2.Print();
    Student s3("赵云",30);
    s3.Print();
    s3 = s2;//s3.operator= (s2);
    s3.Print();
    int a = 10,b = 20,c = 30;
    (a = b) = c;//赋值表达式的值是左值的引用
    cout << a << endl;
    Student s4("关羽",40);
    (s4 = s3) = s1;
    s4.Print();
    Student s5 = s2;//拷贝构造,因为以前没有构造过s5，所以第一次给s5赋值一定是拷贝构造
    s5.Print();
    Student *ps = new Student(s5);//拷贝构造,同理
    ps->Print();
    delete ps;
    return 0;
}
#if 0
5）拷贝构造只能解决构造对象副本时的深拷贝问题，缺省方式的拷贝赋值仍然是按字节复制。
这种情况下就需要提供一个自定义的拷贝赋值运算符函数，以获得真正意义上的对象副本。
class 类名{  （（operator=） 是函数名）
	类名& operator= （const 类名& obj）{
	以拷贝的方式从obj复制成员变量的值（当然也可以在初始化表里做复制）
}
};
注意：A.先释放已有的资源，然后从拷贝源复制资源
	B.防止自赋值
	C.返回自引用，以支持连续赋值
#endif
