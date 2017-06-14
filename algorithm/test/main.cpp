#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    set<string> s1,s2,diff;
    s1.insert("6f5d5a8c-a648-484c-84bc-6537c2c70aa7");
    s1.insert("f2e1635c-eaff-48c7-9d35-53e85b690818");
    s1.insert("319ffc28-5336-4a28-be54-613e19df0eb8");
    s2.insert("6f5d5a8c-a648-484c-84bc-6537c2c70aa7");
    s2.insert("3d1553be-1b7f-432f-b2ce-36c0f8c49283");
    s2.insert("e60a45a4-67cf-4a83-bcee-acd733face1a");
    std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                        std::inserter(diff, diff.begin()));
    for (auto i : s1) std::cout << i << endl;
    std::cout << "minus " << endl;
    for (auto i : s2) std::cout << i << endl;
    std::cout << "is: " << endl;

    for (auto i : diff) std::cout << i << endl;
    return 0;
}

