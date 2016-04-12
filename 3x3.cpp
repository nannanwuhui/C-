/**
 * 实现一个3x3整型矩阵，支持如下运算：
 * ＋，*,+=,*=,前后缀＋＋，<<
 */
#include <iostream>
#include <iomanip>
using namespace std;
class M33{
public:
    M33(void){
        for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3;j++)
                m_a[i][j] = 0;
    }
    /**
     * int (*p)[3],写成这样的形式也是可以的，和int a[][3]一样都是行指针
     * int a[3][3]二维数组作为参数第一个3是可以不写的，其实就是一个行指针。
     * 数组是不能整体赋值的，只能一个一个的赋值，所以数组的初始化不能在
     * 初始化表里完成
     * 当然可以使用memcpy来完成，大小是9*sizeof(int)
     */
    M33(int a[][3]){
        for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3;j++)
                m_a[i][j] = a[i][j];
         
    }
    M33 operator+(const M33& m)const{
        int a[3][3];
        for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3;j++)
                a[i][j] = m_a[i][j] + m.m_a[i][j];
        return M33(a);
    }
    M33 operator*(const M33& m)const{
        int a[3][3] = {0}; 
        for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3;j++)
                for(int k = 0;k < 3;k++)
                    a[i][j]+=m_a[i][k]*m.m_a[k][j];
        return M33(a);
    }
    M33& operator+=(const M33& m){
         return *this = *this + m;
    }
    M33& operator*=(const M33& m){
        return *this = *this * m; 
    }
    //前++,前++可以连用
    M33& operator++(void){
        for(int i = 0;i < 3;i++)
            for(int j = 0;j < 3;j++)
                m_a[i][j]++;
        return *this;
    }
    const M33 operator++(int){
        //缺省的拷贝赋值按字节复制
        M33 m = *this;
        ++(*this);
        return m;
    }
    friend ostream& operator<< (ostream& os,const M33& m){
         for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                os << setw(4) << m.m_a[i][j];
            }
            os << endl;
         }
         return os;
    }
private:
    int m_a[3][3];
};
int main(void){
    int a1[3][3] = {1,2,3,4,5,6,7,8,9};
    M33 m1(a1);
    int a2[3][3] = {9,8,7,6,5,4,3,2,1};
    M33 m2(a2);
    cout << "m1 + m2" << endl;
    cout << m1 + m2 << endl;
    cout << "m1 * m2" << endl;
    cout << m1 * m2 << endl;
    M33 m3(m1);
    cout << "m3+=m2" << endl;
    m3 += m2;
    cout << m3 << endl;
    m3 = m1;
    cout << "m3*=m2" << endl;
    m3 *=  m2;
    cout << m3 << endl;
    m3 = m1;
    cout << "后++" << endl;
    cout << m3++ <<endl;
    m3 = m1;
    cout << "前++" << endl;
    cout << ++m3 << endl;
    cout << m3 << endl;
    return 0;
}
