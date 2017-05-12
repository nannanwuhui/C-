#include <tea/tea.h>
#include <vector>
#include <iostream>
#include <list>
template <typename T>
void printElements(const T& coll){
    for(const auto& elem : coll){
        std::cout << elem << std::endl;
    }
}
void print(){
    std::vector<int> v{1,2,3,4,5,6};
    auto it = v.begin();
    for(;it != v.end();it++){
        Debug("%d",*it);
    }
}
void print1(std::initializer_list<int> vals){
    auto it = vals.begin();
    for(;it != vals.end();it++){
        Debug("%d",*it);
    }
}
void print2(){
    for(int i : {1,2,3,4,5,6,7,8,9,10}){
        Debug("%d",i);
    }
}
void print3(){
    std::vector<int> v{1,2,3};
    for(auto& elem : v){
        elem *= 3;
        Debug("%d",elem);
    }
}
int main(){
    Debug("************ print: *****************");
    print();
    Debug("************ print1: *****************");
    print1({6,5,4,3,2,1});
    Debug("************ print2: *****************");
    print2();
    Debug("************ print3: *****************");
    print3();
    Debug("************ printElements: *****************");
    std::list<int> list{1,2,3};
    printElements<std::list<int> >(list);

    return 0;
}


