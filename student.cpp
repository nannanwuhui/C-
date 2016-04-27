#include <iostream>
using namespace std;
class Student{
public:
    /*Student(){
        m_strName = "没名";
        m_nAge = 0;
    }
    Student (string strName,int nAge){
        m_strName = strName;
        m_nAge = nAge;
    }*/
    /*Student (string strName = "没名",int nAge = 0){
        m_strName = strName;
        m_nAge = nAge;
    }*/
    Student (string strName = "没名",int nAge = 0):m_strName(strName),m_nAge(nAge){

    }
    void Learn(string strLesson){
        cout << "I am" << m_strName << ",this year" << m_nAge << "old,I am learning" << strLesson << "." << endl;
        //cout << "我是" << m_strName << ",今年" << m_nAge << "岁，我在学" << strLesson << "." << endl;　
    }
    bool SetName(string strName){
        if(strName.length() == 0)
            return false;
        m_strName = strName;
        return true;
    }
    string GetName(void){
        return m_strName;
    }
    bool SetAge(int nAge){
        if(nAge <= 0)
            return false;
        m_nAge = nAge;
        return true;
    }
    int GetAge(void){
        return m_nAge;
    }
    void Play(string strGame);
private:
    string m_strName;
    int m_nAge;

};
int main(){
    //在栈中隐式构造对象
    Student student("张飞",25);
    //student.m_strName　=　"张飞"；//在类的外部不能访问私有成员
    /*if(!student.SetName("张飞"))
    {
        cout << "设置姓名失败!" << endl;
        return -1;
    }
    if(!student.SetAge(25)){
        cout << "设置年龄失败!" << endl;
        return -1;
    }
    
    cout << student.GetName() << "," << student.GetAge() << endl;
    */
    student.Learn("C++语言");
    //在栈中显式构造对象
    Student student2 = Student("关羽",40);//显示构造，不是在调用构造函数（没有返回值）,初始化，不是赋值
    student2.Learn("英语");
    //在栈中构造对象数组
   /* Student students[3] = {　//这里可以不给3,初始化几个就是几个
        Student("赵云",28),
        Student("刘备",39),
        Student("曹操",50),//这里的,有没有都可以
    };*/
    /*students[0].Learn("汉语");
    students[1].Learn("数学");
    students[2].Learn("物理");
    */
    //在堆中构造对象
    Student *pStudent = new Student("诸葛亮",38);
    pStudent->Learn("化学");
    delete pStudent;
    /*Student *pStudents = new Student[3] = {
        //需要c++2011支持，这是新版本的编译器
        Student("赵云",28),
        Student("刘备",39),
        Student("曹操",50),//这里的,有没有都可以
    }*/
    //这样定义会去调用类的无参构造
    //在堆中构造对象数组
    Student *pStudents = new Student[3];
    //*(pStudents + 0)
    pStudents[0].Learn("生物");
    delete[] pStudents;
    //编译器会理解成是函数声明
    //Student s1();
    //构造对象的时候使用无参构造，不用加（）
    Student s1;
    s1.Learn("语文");
    //这样写编译器不会当成函数声明
    //Student *ps = new Student(); 可以
    Student *ps = new Student;//运行时才会分配内存 
    ps->Learn("法语");
    ps->Play("wow");
    delete ps;
    return 0;
}
//成员函数可以定义在类的外边,甚至是另外一个cpp文件中也是可以的（编译的时候要和main所在的cpp文件一起编译）。
void Student::Play(string strGame){
    cout << "我在玩" << strGame << endl;
}
#if 0
６）初始化表
class　类名｛
	类名（形参表）：成员变量（初始值），...｛
		构造函数体：
｝
｝；
构造函数，在执行你写的代码之前，g++编译器编译完了以后，会在你的代码之前加上很多代码，主要的工作（创建对象）是创建成员变量并初始化，
如果成员变量是栈内存基本类型，则开辟内存即可,如果指定了初始表，当然会初始化
如果成员变量是堆内存基本类型，则开辟内存并会初始化成0.
如果成员变量是类类型，则会调用类的缺省构造函数
创建成员变量的时候是按照定义的顺序去创建的，不是按照初始化表的顺序初始化。
class Dumy{
public:
	Dumy(string str):m_str(str),m_len(m_str.length()){
	/*因为是先初始化m_len，而这个时候m_str还没有被初始化，所以用它来求出字符串长度肯定是不对的。*/
}
private:
	int m_len;（这里只是声明，用这个类创建对象的时候才会去开辟内存，这个时候，如果有初始化表，就会用初始化表去做初始化，如果没有提供初始化表，就会去用默认的方式做初始化，栈内存不初始化，堆内存用0初始化，类类型用无参构造去初始化）
	string m_str;
}
解决方法：
两种：
１、在private里先定义m_str,后定义m_len;
２、初始化表用：Dumy(string str):m_str(str),m_len(str.length())｛｝
声明　　定义（开辟内存空间）　初始化

类是一种描述，定义一个类是在定义一个数据类型。相当于盖房子的图纸
类是一个源码级的概念，不是运行时的概念，对象是存在于内存空间的。
创建对象，实例化是运行期的概念，
调用构造函数，根据参数列表去初始化，分配内存空间都是运行时的概念！
#endif
