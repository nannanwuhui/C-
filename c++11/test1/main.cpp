#include <iostream>

using namespace std;
class A{
public:
    A(int id):m_id(id){}
    void operator()(){
        cout << "m_id:" << m_id << endl;
        ++m_id;
    }
private:
    int m_id;
};
int main()
{
    int x = 0;
    int y = 42;
    auto qqq = [x,&y]{
        cout << "x:" << x << endl;
        cout << "y:" << y << endl;
        ++y;
    };
    x = y = 77;
    qqq();
    qqq();
    cout << "final y:" << y << endl;

    int id = 0;
    auto f = [id]()mutable{
        cout << "id:" << id << endl;
        ++id;
    };
    id = 42;
    f();
    f();
    f();
    cout << id << endl;

    int tmp = 5;
    A a(tmp);
    a();
    a();
    a();
    cout << "tmp:" << tmp << endl;
    return 0;
}

