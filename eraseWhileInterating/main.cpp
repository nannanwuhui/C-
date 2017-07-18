#include <iostream>
#include <map>
#include <stdint.h>
using namespace std;

int main()
{
    typedef map<int32_t,int32_t> Map;
    Map m;
    m.insert(make_pair(1,1));
    m.insert(make_pair(2,2));
    m.insert(make_pair(3,3));
    Map::iterator it = m.begin();
    for(;it != m.end();){
#if 0
        //http://en.cppreference.com/w/cpp/language/operator_precedence
        //https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it
#endif
        m.erase(it++);
    }
    return 0;
}

