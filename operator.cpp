#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream

class value_string
{
public:
    std::string v;
    friend std::ostringstream& operator << (std::ostringstream& oss, value_string& v_type);
    friend std::ostream& operator << (std::ostream& oss, value_string& v_type);
    value_string(std::string _v)
        :v(_v)
    {
    }
};

std::ostringstream& operator << (std::ostringstream& oss, value_string& v_type)
{
    oss <<v_type.v;
    return oss;
}

std::ostream& operator << (std::ostream& oss, value_string& v_type)
{
    oss <<v_type.v;
    return oss;
}

int main()
{
   std::string s1 = "hello ";
   value_string v1(s1);
   std::ostringstream oss;

   std::string x("world");
   oss << v1 << x;
   std::cout << oss.str() << std::endl;
   std::cout << v1 << x << std::endl;

  return 0;
}
