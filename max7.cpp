#include <iostream>
using namespace std;
class Comparator{
public:
    Comparator(int x,int y):m_x(x),m_y(y){}
    int max(void) const {
        return m_x > m_y ? m_x:m_y;
    }
private:
    int m_x;
    int m_y;
};
int main(void){
    Comparator c1(100,200);
    cout << c1.max() << endl;
}
