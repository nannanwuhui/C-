#include <iostream>
using namespace std;
/**
  * C++的编译器是从前往后看的，比如说你在一个类里用到了另外一个类，
  * 但是另外的这个类的定义是在下面定义的，这个叫做交叉类，这个时候就需要把另外的这个类声明一下。
  */
class Point2D;
class Point3D{
public:
    /**
     * explicit用在这里的意思是，下面的这个构造函数如果用作类型转换的话，一定要是显式类型转换
     * 避免无意识的造成类型转换，引起错误。这样会提醒程序员，如果真的就是要做类型转换，那
     * 就做显式的类型转换
     * 提供了隐式的规则，又强制的加上explicit不能做隐式的转换,只能做显式的转换，以防止隐式的规则引入潜在的错误。
     * 可以用于类型转换的构造函数是定义在目标类型里
     */
    explicit Point3D(int x = 0,int y = 0,int z = 0):m_x(x),m_y(y),m_z(z){
        
    }
    /*Point3D(const Point2D& pt2):m_x(pt2.m_x),m_y(pt2.m_y),m_z(0){
    
    }*/
    Point3D(const Point2D& pt2);
    void Print(void){
        cout << m_x << "," << m_y << "," << m_z << endl;
    }
private:
    int m_x;
    int m_y;
    int m_z;
};

class Point2D{
public:
    Point2D(int x,int y):m_x(x),m_y(y){
        
    }
    void Print(void){
        cout << m_x << "," << m_y << endl;
    }
    /**
     * 明明没有返回类型却返回了一个Point3D,
     * 注意返回的类型一定是和operator后面写的这个类型是一致的
     * 当要把一个Point2D赋给一个Point3D的时候，就会调用这个类型转换运算符
     * 函数
     * 而类型转换运算符函数是用在源类型里
     */
    operator Point3D(void){
        return Point3D(m_x,m_y,1000);
    }
private:
    int m_x;
    int m_y;
    /**
     * 这样Point3D这个类就可以访问Point2D这个类里的私有成员了。
     */
    friend class Point3D;//写在上面也可以,不一定要放在private里
};
/**
 * 这其实是定义了一种转换规则。当pt3 =
 * pt2,它会用pt2做参数去调用一下这个构造函数构造出一个临时的pt3,
 * 然后再用这个临时的pt3赋值给pt3.
 * 自定义类型转换构造函数
 */
Point3D::Point3D(const Point2D& pt2):m_x(pt2.m_x),m_y(pt2.m_y),m_z(0){
    
}
int main(){
    Point3D pt3(10,20,30);
    pt3.Print();
    Point2D pt2(100,200);
    pt2.Print();
    /**
     * pt3 = pt2;
     * 如果用于类型转换的构造函数和类型转换运算符函数都提供的话，编译器会选择
     * 类型转换运算符函数
     * 当用隐式转换的时候，编译器会优先选择类型转换运算符函数
     */
    //pt3 = pt2;
   /**
    * 当用显式转换的时候，编译器会优先选择构造函数
    */
    pt3 = static_cast<Point3D>(pt2);
    pt3.Print();
    /**
     * 调用pt3的构造函数构造一个临时的pt3，然后把它赋值给pt3.
     */
    //pt3 = 1000;//这一行不对,没有对应的构造函数，也没有对应的类型转换运算符函数
    pt3 = static_cast<Point3D>(1000);
    pt3.Print();
    return 0;
}
#if 0
３)类型转换运算符：
构造和析构函数没有返回类型
在源类型中定义一个如下形式的运算符函数：
没有返回类型却有返回值，很怪异,但这是对的
operator 目标类型(void){
	构造一个目标类型的对象，返回之；
}
如果在源类型中提供类型转换运算符函数的同时，在目标类型中定义类型转换构造函数，
对于隐式类型转换，系统会优先选择类型转换运算符函数完成类型转换，
而对于显式类型转换，系统则会优先选择构造函数完成同样的工作。
但是在实际的工作中，最好不要同时提供类型转换运算符函数和类型转换构造函数。
但是这点可以用于解决别人代码的bug.
在老标准的c++中，构造函数可以使用explicit关键字来强制使用显式的转换，但是类型转换运算符函数不可以使用explicit关键字，
在最新2011的c++标准中，类型转换构造函数和类型转换运算符函数都可以使用explicit关键字来强制使用显式类型转换。
#endif
