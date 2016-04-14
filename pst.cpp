#include <iostream>
using namespace std;
class Person{
public:
    Person(const string& strName,int nAge):m_strName(strName),m_nAge(nAge){
        cout << "我是" << m_strName << ",今年" << m_nAge << "岁" << endl; 
    
    }
    void Eat(const string& strFood){
        cout << strFood << "真好吃!" <<endl;
    }
protected:
    string GetName(void){
        PriFunc();
        return m_strName;
    }
private:
    void PriFunc(void){
        cout << "基类中的私有成员函数" << endl;
    }
    string m_strName;
    int m_nAge;
};
class Student:public Person{
public:
    /**
     * 在初始化列表中通过调用基类的构造函数来完成对基类中声明的属性的初始化工作
     */ 
    Student(const string& strName,int nAge,int nNumber):Person(strName,nAge),m_nNumber(nNumber){
        cout << "我是学生，学号是" << m_nNumber << "." << endl; 
    
    }
    void Learn(const string& strLesson){
        cout << "我在学习" << strLesson << "我的学号是"<< m_nNumber << endl;
        /**
         * 这样写的话，如果用Student类型的指针(赋给这个指针的是一个Person类型的内存)去
         * 访问Learn函数，这样的相当于去访问一个不属于你的内存，可能会出段错误
         */
        m_nNumber = 9999;
    }
    void foo(void){
        //cout << m_strName << endl;
        cout << GetName() << endl;
        //PriFunc();
    }
    /*void Eat(const string& strFood){
        cout << "子类中的Eat()函数" << endl; 
    }*/
    int Eat(void){
        cout << "子类中的Eat()函数" << endl; 
        Person::Eat("巧克力");
        return 100;
    }
private:
    int m_nNumber;
};
class Teacher:public Person{
public:
    Teacher(const string& strName,int nAge,const string& strJob):Person(strName,nAge),m_strJob(strJob){
        cout << "我是教师，职务是" << m_strJob << "." << endl;
    }
    void Teach(const string& strSubject){
        cout << "我在教" << strSubject << "." << endl;
    }
private:
    string m_strJob;
};
int main(void){
    /**
     * 当你在构造子类的时候，基类是要先被构造的，因为基类是子类的一部分
     * 子类对象要比基类对象大
     * 
     */ 
    Student s1("张飞",28,1001);
    //s1.Eat("面条");
    cout << s1.Eat() << endl;
    /**
     * 隐藏并不代表没有了，可以通过加上Person::指明调用从基类中继承过来的
     * 那个Eat();
     */
    s1.Person::Eat("面条");
    s1.Learn("C++");
    /**
     * 通过基类的公有函数可以去间接的访问基类的私有部分，这说明
     * 基类的私有部分子类确是继承过来了
     */
    s1.foo();
    Teacher t1("赵云",50,"教授");
    //t1.Eat("包子");
    t1.Teach("物理");
    
    //Person p1("张飞",66);
    /**
     * 保护的成员函数在main函数中不能访问，只能在子类中访问
     */
    //cout << p1.GetName() << endl;
    /**
     * 把一个子类对象的地址赋给一个基类类型的指针
     * 把一个子类对象的别名用一个基类类型的引用来表示
     * 都是没有问题的。
     * 子类-基类 子集-原集合
     */
    Person* pPerson = new Student("关羽",22,1002);
    pPerson->Eat("米饭");
    //pPerson->Learn("Java");
    /**
     * 成员变量是在对象里
     * 而成员函数不在对象里,而是在类里(代码段里)
     * 如果一个类里定义了一个函数，它就会被编译，这个函数就会存在于代码段中
     *
     */
    Person person("曹操",40);
    //Student* pStudent = (Student*)new Person("曹操",40);
    Student* pStudent = (Student*)&person;

    /**
     * 只要有一个Student类，通过Student指针就可以调用任何Student的成员函数
     * 不管赋给pStudent的地址是不是Student类型的都可以。
     * 但是如果这个成员函数中试图去访问Student数据成员（成员变量）的时候
     * 是有可能出问题的。
     */
    //pStudent->Eat("火烧");
    //pStudent->Eat();
    /**
     * 如果是在栈里，应该是一个不知道是什么的数，
     * 而如果在堆里，很可能是0,因为内存在分配的时候不一定就是分配和你指定的内存大小一样
     * 往往是比你指定的内存大很多,
     * 并且在类里描述的堆内存往往在创建对象的时候会被初始化成0
     */
    pStudent->Learn("英语");
    return 0;
}
