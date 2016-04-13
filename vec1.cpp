#include <iostream>
//每一个容器都有自己的头文件,头文件的文件名和容器的名字是一样的
//一般来讲，以后所有使用数组的地方都可以用向量来代替了，向量的功能只会比数组强，不会比数组弱
#include <vector>
/**
 * 所有的STL容器的名字空间也是std
 * c++的标准库只有一个名字空间,都是std
 * 有了std,io流可以用了,STL的库你也能用
 */
using namespace std;
void show(const vector<int>& vi){
    //所有的STL容器都有size()函数，都是用size()获取元素的个数
    size_t size = vi.size();
    cout << "大小：" << vi.size() << endl;
    for(size_t i = 0;i < size;++i)
        cout << vi[i] << ' ';
    cout << endl;
}
int main(){
    vector<int> v1;//空向量，不占内存
    show(v1);
    vector<int> v2(5);
    v2[0]=10;
    v2[2]=30;
    v2[4]=50;
    show(v2);
    vector<int> v3(5,1000);
    show(v3);
    int a[] = {100,200,300,400,500};
    vector<int> v4(a,a+5);
    show(v4);
    vector<int> v5 = v4;//拷贝构造（STL支持深拷贝）
    v5.pop_back();
    v4[4]++;
    show(v5);
    show(v4);
    v4.push_back(1234);
    show(v4);
    cout << v4.front() << endl;
    cout << v4.back() << endl;
    /**
      *list<int>内部的内存是不连续的，vector<int>内部的内存是连续的，但是这里
      * 我们打印的方法完全一样，这就是迭代器给我们带来的方便，但是list和vector内部
      * 的迭代器的实现肯定是不一样的
      */
    for(vector<int>::iterator it = v4.begin();it != v4.end();++it)
        cout << *it << ' ';
    cout << endl;
    vector<int>::iterator it = v4.begin();
    *it = 1;//v4[0] = 1;
    /**
      *　迭代器里封装了一个int*,做完地址和一个整数相加以后，返回
      * 相加以后的地址，然后对返回后的地址做解引用，就可以操作容器中的
      * 元素了
      */
    *(it + 1) = 2;//v4[1] = 2;
    *(it + 2) = 3;//v4[2] = 3;
    show(v4);
    //it指向被删除元素的下一个元素
    it = v4.erase(it + 3);
    show(v4);
    //it指向插入的元素,在迭代器it所指向元素的前面插入
    it = v4.insert(it,4);
    show(v4);
    //反向迭代器，当你面向首端的时候，是反向迭代器，
    //当你面向尾端的时候，是正向迭代器
    for(vector<int>::reverse_iterator it = v4.rbegin();it != v4.rend();++it)
        cout << *it << ' ';
    cout << endl;
    //一个普通的迭代器可以被隐式的转换成常迭代器
    vector<int>::const_iterator cit = it;
    cout << *it << endl;//4
//    ++*cit;//常迭代器相当于常指针，指向的目标不可被修改
    /**
      * 如果一个迭代器不能移动，也就是不能迭代，那迭代器就没有任何价值
      * 因为迭代器就是为了迭代而存在的
      */
    cit += 2;//常迭代器本身可以被修改
    cout << *cit << endl;
    vector<int> v6(1,100);
    it = v6.begin();
    cout << *it << endl;//100
    /**
      * 向向量里放东西的时候有可能会使其内部结构发生变化，不是简单的在后面加上一个元素
      * 就可以了，它的内存布局是要调整的,比如连续的内存不够了，它就需要另外开一块连续的内存，
      * 然后把现在内存里的东西拷贝过去，100这个元素的地址肯定变了，但是it还存放着100以前的地址，
      * 所以*it肯定就不是100了。it就会变成野指针。
      * it被初始化以后就和容器没有关系了，容器的内部结构发生变化，it里存放的地址不会同步
      * 如果只是遍历一下，对以前的元素做个++,--,容器内部的结构没有发生变化，那it肯定还是有效
      * 的,可以直接用，但是如果做了，push_back(),pop_back(),insert(),erase()这些可能使容器的结构发生
      * 变化的操作以后，迭代器应该重新初始化以后再使用才安全，当然也可能连续的内存够用，
      * it没有失效，勉强能用，但是没人能够保证it一定能用。
      */
    v6.push_back(200);
    it = v6.begin();
    cout << *it << endl;//0,重新初始化以后100
    return 0;
}
