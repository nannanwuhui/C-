#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

class Contact
{
public:
    bool operator < (const Contact& rhs) const{
        return m_id < rhs.m_id;
    }
    string m_id;
    int    m_idx;
    string m_userName;
    string m_domain;
};
ostream& operator<< (ostream& os,const Contact& c)
{
    return os<< c.m_id;
}

int main()
{
    set<Contact> s1,s2,diff;
    Contact ct,ct1,ct2;
    ct.m_id = "d5c19e66-7b64-4c1a-8be2-058314cc090d";
    ct1.m_id = "c8b3891e-6eb4-40e4-9cb6-6a335e630151";
    ct2.m_id = "d045a220-5109-4850-a5da-de727dee6b25";
    s1.insert(ct);
    s1.insert(ct1);
    s1.insert(ct2);
    ct.m_id = "d5c19e66-7b64-4c1a-8be2-058314cc090d";
    ct1.m_id = "c8b3891e-6eb4-40e4-9cb6-6a335e630151";
    ct2.m_id = "77b98715-57e1-467c-8145-5aebaee8d69d";
    s2.insert(ct);
    s2.insert(ct1);
    s2.insert(ct2);

    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                        std::inserter(diff, diff.begin()));
    for (auto i : s1) std::cout << i << endl;

    std::cout << "minus " << endl;
    for (auto i : s2) std::cout << i << endl;
    std::cout << "is: " << endl;

    for (auto i : diff) std::cout << i << endl;
    return 0;
}

