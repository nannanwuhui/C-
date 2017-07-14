#include <iostream>
#include <map>
#include <stdint.h>
//使用m[]这种方式访问map有副作用:比如访问key = 0的元素，如果原来map里没有，则会创建
using namespace std;
typedef map<int8_t,int8_t> Map;
int main()
{
    Map m;
    cout << "m.empty: " << m.empty() << endl;
    cout << m[0] << endl;
    cout << "m.empty: " << m.empty() << endl;
    Map::iterator it = m.find(0);
    if(it == m.end()){
        cout << "没有找到key = 0的元素";
    }
    else{
        cout << "找到了key = 0的元素，value=" << m[0] << endl;
    }
    return 0;
}
#if 0
运行结果：
m.empty: 1

m.empty: 0
找到了key = 0的元素，value=
#endif
