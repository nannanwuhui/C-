#include <iostream>
using namespace std;
class Student;
class Teacher{
public:
  /*  void educate(Student* pStudent){
        pStudent->ask("什么是this指针？",this);
        cout << m_strAnswer <<endl;
    }*/
    void educate(Student* pStudent);

    void reply(const string strAnswer){
        m_strAnswer = strAnswer;
    }
private:
    string m_strAnswer;
};
class Student{
public:
    void ask(const string& strQuestion,Teacher *pTeacher){
        cout << strQuestion << endl;
        pTeacher->reply("this指针就是指向调用对象的指针");
    }
};
void Teacher::educate(Student* pStudent){
    pStudent->ask("什么是this指针？",this);
    cout << m_strAnswer <<endl;
}
int main(){
    Teacher t;
    Student s;
    t.educate(&s);
    return 0;
}
#if 0
4）this指针可以作为函数的参数实现对象间交互。
#endif
