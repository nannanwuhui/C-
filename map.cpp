#include <iostream>
#include <map>
using namespace std;
class ChrCmp{
public:
    bool operator()(char a,char b){
        //小于比较器本来应该a<b的时候返回true，但是现在是a > b的时候返回true
        //所以就会大的数放在左子树，小的放在右子树
        return a > b;
    }
};
class Candidate{
public:
    //map需要调用无参构造构造临时变量
    Candidate(const string& name = ""):m_name(name),m_votes(0){}
    const string& name()const{
        return m_name;
    }
    const size_t& votes()const{
        return m_votes;
    }
    void votes(){
        ++m_votes;
    }
private:
    string m_name;
    size_t m_votes;
};
int main(){
//    map<char,Candidate> cs;
    map<char,Candidate,ChrCmp> cs;
    cs.insert(pair<char,Candidate>('A',Candidate("张飞")));
    cs.insert(make_pair('B',Candidate("赵云")));
    cs['C'] = Candidate("关羽");
    cs['D'] = Candidate("刘备");
    cs['E'] = Candidate("曹操");
    typedef map<char,Candidate>::iterator IT;
    typedef map<char,Candidate>::const_iterator CIT;
//    pair<IT,bool> res = cs.insert(make_pair('B',Candidate("坏蛋")));
    pair<IT,bool> res = cs.insert(make_pair('F',Candidate("坏蛋")));
    if(! res.second)
        cout << "插入失败!" << endl;
    else
        cout << "插入成功:" << res.first->second.name() << endl;

    for(size_t i = 0;i < 10;i++){
        for(CIT it = cs.begin();it != cs.end();++it)
            cout << '[' << it->first << ']' << it->second.name() << ' ';
        cout << endl << "请投下庄严的一票：" << flush;
        char key;
        cin >> key;
        IT it = cs.find(key);
        if(it == cs.end()){
            cout << "废票！" << endl;
            continue;
        }
        it->second.votes();
    }
    CIT win = cs.begin();
    for(CIT it = cs.begin();it != cs.end();++it){
        cout << it->second.name() << "获得" << it->second.votes() << "票" << endl;
        if(it->second.votes() > win->second.votes())
            win = it;
    }
    cout << "热烈祝贺" << win->second.name() << "同学" << "光荣当选为首席保洁员!" << endl;
    return 0;
}
#if 0
映射：
一个平衡有序二叉树所存储的一个key-value对的集合。
树上的每一个节点都是一个key和一个value组成的一个对。
那么这个对在STL中用什么样的对象来表达呢？
显然不能用一个简单的数组来放，因为数组来放的话，两个元素必须同种类型。
但是我们知道key和value的类型可以是不一样的，可以是不同类型的。
所以这里引入了一种新的容器，这个容器没有被放在十大容器之内，因为它算不上一个很大的容器，这个容器很小，小到只能放两个元素。但是这两个元素可以是不同类型的。这个容器就是Pair。这个容器有两个元素，第一个元素叫first，第二个元素叫second。
用Pair来表达一个map容器的任何一个节点。key就放在first里，value就放在second里。
以key作为比较的基准。
左小右大，有序树，
而且对于映射来说，它的key一定是唯一的。key是不允许重复的。
利用有序树在搜索方面的优点。
有序树搜索很快。搜索性能可以达到对数级的时间复杂度。
从根节点开始，比根节点大，左子树砍掉，
　　　　　　　比根节点小，右子树砍掉。
有序树的时间复杂度相当于一个二分查找，但是二分查找比较麻烦，必须先有序才行。
先排序，在一个线性表里面去排序，排序本身就要花时间。
所以索性不用线性表了，直接用一个树状结构。放的时候就保证有序。
插入和删除的性能可能不是特别高，主要是用于搜索，统计。
１、映射是一个key-value对的序列，其中每个key都是唯一的
２、映射中所有的key-value对，按key的升序排列。
３、以有序二叉树的形式存储。
４、映射可以根据key快速地找到与之对应的value。
５、利用key类型的”<”运算符比大小
－map<string,int> si;
６、利用针对key的小于比较器比大小
－map<string,int,Less> si;
把一个类型用映射来存储的时候，就需要考虑比较的方式。<还是小于比较器
７、映射支持以key为索引的下标操作。
－value_type& operator[](const key_type& key);
返回与参数key相对应的value,若key不存在，则新建一个key-value对，value按缺省的方式初始化。注意返回值是value_type的引用，当然是可以作为左值来使用的.
８、映射的基本访问单元为pair,pair只有两个成员变量，first和second，分别表示key和value.
－map<string,int> si;
si.insert(pair<string,int>(“beijing”,1));//直接定义pair对象
si.insert(make_pair(“tianjin”,2));//make_pair为全局的工厂函数，可以直接创建一个pair;
si[“shanghai”] = 3;//直接使用下标运算符隐式的构建pair，这种方式显得更直接
map<string,int>::iterator it = si.begin();
迭代器指向的是piar类型的对象
cout << it->first << “-” << it->second << endl;
９、常用成员函数
－插入元素
pair<iterator,bool> insert(const pair<key_type,value_type>& pair);
iterator表示插入的位置，bool表示插入成功还是失败。
如果成功，bool值为true，iterator指向新插入的元素
如果bool值为false,表示插入失败，就不要再用iterator了，没有意义。
为什么会插入失败呢？内存不够了或者是key重复了（map中的key必须唯一）

插入位置由映射根据key的有序性确定
－删除元素
void erase(iterator pos);
删除指定位置的元素
void erase(iterator begin,iterator end);
删除指定范围的元素
size_type erase(const key_type& key);
删除指定key的元素
－查找匹配元素，成功返回指向查找元素的迭代器，失败返回终止迭代器
iterator find(const key_type& key);
在映射中查找既不需要“==”运算符，也不需要等于比较器，仅支持针对key的小于比较即可
既然已经有全局的find函数了，为什么映射还要搞一个自己的find函数呢？
因为全局的find是线性搜索。而映射的find是树搜索。
比如要是把一个类类型的对象放在向量里面，如果需要调用全局的find的话，这个类是需要支持==运算符的。因为线性查找，需要一个一个的比较是否相等。
映射里面，比如说a既不小于b,也不大于b,那就是等于b了。
需要频繁的大量的搜索的话，首选映射.根据某个元素的特征进行搜索的话，用映射比较合适．
map缺省情况下是按照左小右大的顺序来放的，
当用迭代器对map进行遍历的时候采用的是中序遍历序，不是前序遍历序，也不是后序遍历序
一个有序树的中序遍历序才会产生有序的结果
当然反向迭代的话，结果就是从大到小了.但是这样没有改变map的内部结构．
但是如果我就是想要改变map的内部结构的话．怎么办？
map默认情况下是左子树小，右子树大.
#endif
