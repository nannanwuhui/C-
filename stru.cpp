#include<iostream>
using namespace std;
struct Student{
    char name[128];
    int age;
    void eat(const char *food){
        cout << "我是"<< name << "，今年" << age << "岁，我在吃" << food << endl;
    }
};
int main(void){
    Student s = {"张飞",27};
    s.eat("KFC");
    Student *ps = &s;
    ps->eat("烧饼");
    return 0;
}
#if 0
１）结构
A、使用结构定义变量可以省略struct关键字
C:
struct Student{
	char name[128];
	int age;
}
struct Student s = {“zhangfei”,22};
C++:
Student s = {“zhangfei”,22}
#endif
