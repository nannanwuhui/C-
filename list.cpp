//双向线性链表
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;
template<typename T>
class list{
public:
    /**
     * 构造，析构（构造函数可能会分配资源，但是构造函数不是唯一一个可以分配资源的地方,析构要把
     * 所有的资源都释放掉）,拷贝构造,拷贝赋值(可以用复制的方式构造一个对象，
     * 当然可以给一个对象赋值)
     * 用头尾指针都为空来表示空链表
     */
    list():m_head(NULL),m_tail(NULL){}
    ~list(){
        //删除所有节点
        clear();
    }
    list(const list& that):m_head(NULL),m_tail(NULL){
        /**
         * 双向线性链表的一个条件：第一个节点的前指针和最后一个节点的后指针为NULL 
         */
        for(node* p = that.m_head;p;p = p->m_next)
            push_back(p->m_data);
         
    }
    list& operator=(const list& that){
        /**
         * 拷贝赋值五大要件:
         * 1、防止自赋值
         * 2、释放原内存
         * 3、分配新内存
         * 4、拷贝新资源
         * 5、返回自引用
         */
        if(&that != this)
        {
            /**
             * 当然这里可以先clear()释放所有的节点，然后把拷贝构造的代码抄一边
             * 更好的做法:复用析构函数和拷贝构造
             */
            /**
             * 拷贝构造(分配新内存，复制(拷贝新资源))
             * 这里按字节复制即可，因为链表中没有动态内存的分配
             */
            list temp(that); 
            /**
             * swap标准库函数，交换两个变量的值
             */
            swap(m_head,temp.m_head);
            swap(m_tail,temp.m_tail);
            /**
             * 上面执行过swap之后，m_head,m_tail持有新链表，temp持有旧链表
             * 由于temp是一个局部变量，当temp离开自己作用域的时候，会调用析构函数
             * 清除所有原来的节点（也就是释放原内存）
             */
        }
        /**
         * 因为赋值运算表达式的值应该是左操作数本身,返回的是自引用。所以
         * 赋值运算符可以连用
         */
        return *this;
    }
    /**
     * 1、获取首元素,返回值可以做左值(可以++,--,-=,/=),返回的不是首元素的副本(减少一次拷贝构造)，
     * 而是首元素的本身
     * 2、假如这个容器具有常属性，比如说常引用，常指针就不能调用front了。
     * 常对象只能调用常函数
     * 非常对象既可以调用非常函数，也可以调用常函数，优先调用非常函数
     * const是用来修饰
     * 如果T&
     * front()const{}这样写明显不合适，因为函数带有const属性，不可以修改成员变量的值，
     * 但是返回的却是非常左值，可以修改成员变量的值
     */
    //不带常属性的调用这个函数，可以修改首元素的值
    T& front(){
        if(empty())
            /**
             * 下溢:已经没有了，你还要拿,这就是下溢
             * 已经满了，你还往里面放，这是上溢
             * 这两个异常是标准库里已经定义好了的异常，不用我们自己定义
             */
            throw underflow_error("链表下溢!");
        return m_head->m_data; 
    }
    //带有常属性的调用这个函数，不可以修改首元素的值
    const T& front(void)const{
        /**
         * 将this指针去常，然后调用front，front()返回的是T&，然后再把T&隐式的转换成const
         * T&(从非常到常可以隐式转换，从常到非常就只能用const_cast<>专业去常工具了)
         * 如果这个不去常的话就是自己调用自己了，会变成无限递归
         * 不去常，this指针是带有常属性的，所以只能调用常函数（就是它自己）
         */
        return const_cast<list *>(this)->front(); 
    }
    /**
     * 有向首部压入和从首部弹出，list明显可以当做堆栈来使用
     * 压入和弹出不需要常属性，因为压入和弹出，容器是要变的，多一个元素，少一个元素，
     * 如果是const的，容器怎么变啊？
     * 如果同时用从首部压入，从尾部弹出，这就是队列了
     * 如果同时用从尾部压入，从首部弹出，也是队列
     * 两个方向的队列
     */
    //向首部压入
    void push_front(const T& data){
         m_head = new node(data,NULL,m_head);
         if(m_head->m_next)
             m_head->m_next->m_prev = m_head;
         else
             m_tail = m_head;
    }
    //从首部弹出
    void pop_front(){
        if(empty()) 
            throw underflow_error("链表下溢!");
        node* next = m_head->m_next;
        delete m_head;
        m_head = next;
        if(m_head)
            m_head->m_prev = NULL;
        else
            m_tail = NULL;
    }
    //获取尾元素
    T& back(){
        if(empty())
            throw underflow_error("链表下溢!");
        return m_tail->m_data;
    }
    const T& back()const{
        return const_cast<list *>(this)->back(); 
    }
    //向尾部压入
    void push_back(const T& data){
         m_tail = new node(data,m_tail);
         if(m_tail->m_prev)
             m_tail->m_prev->m_next = m_tail;
         else 
             m_head = m_tail;
    }
    //从尾部弹出
    void pop_back(){
        if(empty())
            throw underflow_error("链表下溢!");
        node* prev = m_tail->m_prev;
        delete m_tail;
        m_tail = prev;
        if(m_tail)
            m_tail->m_next = NULL;
        else 
            m_head = NULL;
    }
    //删除所有匹配元素
    void remove(const T& data){
        for(node* p = m_head,*next;p;p = next){
            /**
             * 这里备一下当前节点的下一个节点，因为如果这个节点匹配成功，就会delete p
             * 这样就没有办法取到p->m_next;了
             */
            next = p->m_next;
            /**
             * list<string>
             * 当用string实例化list的时候，可以这样用，因为string类重载了
             * ==运算符，但是如果用const char*实例化list<>，就不行了，显然，
             * 如果是const char*的话，字符串比较是不能用==的,
             * 用==是在比较字符串的地址
             * 所以const char*这种类型就不适用了，可以考虑做局部特化，但是还是觉得
             * 划不来，因为就只有这一行需要做修改，其他都不用。
             * 可以把和类型有关的东西尽量的都封装在一个函数里,这样的话,我如果需要特化,
             * 只需要特化一个很小的函数就可以了,
             * 如果像现在这样,把类型相关的和类型无关的全都搅合在一块,就必须把整个remove整体
             * 做特化,但是这里%99的代码是重复的,如果我把类型相关和类型无关的部分拆开,这样只需要
             * 把类型相关的部分特化一下就行了,工作量就可以极大的减小.
             */
            //if(p->m_data == data){
            if(equal(p->m_data,data)){
                //注意考虑边界条件
                if(p->m_prev)
                    p->m_prev->m_next = p->m_next; 
                else
                    m_head = p->m_next;
                   //m_head->m_prev = NULL;这里不再需要这一行，下面169行已经保证了
                if(p->m_next)
                    p->m_next->m_prev = p->m_prev;
                else 
                    m_tail = p->m_prev;
                delete p; 
            }
        }
    }
    //清空链表
    void clear(){
        for(node* next;m_head;m_head = next){
            next = m_head->m_next;
            delete m_head;
        }
        m_tail = NULL;
    }
    //判空
    bool empty()const{
        //其实按照我们的实现，不可能一个为NULL,一个不为NULL。要么都是NULL,要么都不是NULL
         return m_head == NULL && m_tail == NULL;
    }
    //获取元素数
    size_t size()const{
       size_t counter = 0;
       for(node* p = m_head;p;p = p->m_next)
           ++counter;
       return counter;
    }
    //插入输出流
    friend ostream& operator<<(ostream& os,const list& lst){
        for(node* p = lst.m_head;p;p = p->m_next){
            os << *p;
        }
        return os;
    }
private:
    class node{
    public:
        node(const T& data,node* prev=NULL,node* next=NULL):
            m_data(data),m_prev(prev),m_next(next){}
        friend ostream& operator<<(ostream& os,const node& n){
            return os<< '(' << n.m_data << ')';
        }
        T     m_data;//数据
        node* m_prev;//前指针
        node* m_next;//后指针
    };
    /**
     * 把与类型相关的独立出来
     * 判等函数的通用版本
     */
    bool equal(const T& a,const T& b)const{
        return a == b; 
    }
    node* m_head;//首指针
    node* m_tail;//尾指针
public:
    /**
     * 迭代器扮演的就是指针,迭代器应该在容器内部实现，并且在外部可见。public
     * 对于一个容器，按照STL的设计来讲，应该提供四种迭代器：
     * 正向迭代器（从前往后），常（表示目标具有常属性）正向迭代器，反向迭代器， 常反向迭代器。
     */
    //正向迭代器
    class iterator{
        public:
        iterator(node* head=NULL,node* tail=NULL,node* p=NULL):m_head(head),m_tail(tail),m_node(p){}
        bool operator==(const iterator& it)const{
            return m_node == it.m_node;
        }
        bool operator!=(const iterator& it)const{
            //相等的反逻辑就是不等，相等的运算符上面已经重载，可以直接使用
            return !(*this == it);
        }
        //前++,结果是一个左值
        iterator& operator++(){
            /**
             * 数组连续内存p++，链表m_node->m_next,用户只需要++即可，
             * 不需要关心底层是用什么来实现的,这样内部结构对用户来说就是
             * 透明的。用户看不见
             */
            if(m_node)
                m_node = m_node->m_next;
            else
                m_node = m_head;
            return *this;
        }
        //后++表达式的结果是一个右值
        const iterator operator++(int){
            iterator old = *this;
            ++*this;
            return old;
        }
        iterator& operator--(void){
            if(m_node)
                m_node = m_node->m_prev;
            else
                m_node = m_tail;
            return *this;
        }
        const iterator operator--(int){
           iterator old = *this; 
           --*this;
           return old;
        }
        /**节点这一层对用户来说是透明的，就是说用户看不到节点，给用户的感觉就是
         * 迭代器直接指向数据
         */
        T&  operator*()const{
            /**
             * 这里的m_node可能为空，这里我们不做安全性检查，由用户来做,因为指针也是由用户
             * 自己来做安全性检查的
             * 当然如果在这里发现m_node为空，可以抛出一个异常
             */
            return m_node->m_data;
        }
        /**
         * 获取指针it->c_str();
         */
        T* operator->()const{
            //别名可以用取地址符&
            return &**this;
        }
        private:
        node* m_head;
        node* m_tail;
        node* m_node;//迭代器对象指向的当前节点。
        /**
         * 通过iterator来对list做插入和删除势必要访问的私有部分
         * 所以把list声明为iterator的友元类
         * list可以访问iterator的私有部分
         */
        friend class list;
    };
    //获取起始正向迭代器
    /**
     * 这里的begin()函数内部也不会修改list类的成员变量，按说是可以加上const属性以
     * 保证安全的，但是由于下面的常正向迭代器的begin()const{},常正向迭代器所指向的
     * 目标一定不可以被修改，所以为了让两个begin()函数构成重载关系，还是常正向
     * 迭代器加上const属性比较合适，end()同理
     */
    iterator begin(){
        return iterator(m_head,m_tail,m_head);
    } 
    //获取终止正向迭代器
    iterator end(){
        //按照STL的设计，所有的终止迭代器都是对应最后一个元素（节点）的下一个,m_tail的下一个就是NULL
        return iterator(m_head,m_tail);
    }
    //在正向迭代器之前插入,返回插入新节点的迭代器
    iterator insert(iterator loc,const T& data){
        if(loc == end()){//loc.m_node == NULL
            /**
            　* 在最后一个iterator之前插入数据，也就是在最后一个节点的下一个
            　* 节点之前插入数据，也就是在m_tail后追加一个节点
            　*/
            push_back(data);
            return iterator(m_head,m_tail,m_tail);
        }
        else{//走到这里，loc.m_node != NULL
            /**
             * 新节点指向前后节点都有了，前后节点指向新插入的节点还没有
             * 这里loc.m_node->m_prev是在list类中访问iterator的私有成员，
             * 所以要在iterator类中加上friend class list,将list声明为
             * iterator的友元，这样list就可以访问iterator的私有成员了
             */
            node* p = new node(data,loc.m_node->m_prev,loc.m_node);
            if(p->m_prev)
                p->m_prev->m_next = p;
            else
                m_head = p;
            /**
             * 这里p->m_next就不用判断是不是NULL了，因为p->m_next就是loc.m_node
             * loc.m_node一定不是NULL
             */
            p->m_next->m_prev = p;
            return iterator(m_head,m_tail,p);
        }
    }
    //删除正向迭代器的目标元素，返回目标元素下一个元素的迭代器
    iterator erase(iterator loc){
        if(loc == end())
            throw invalid_argument("无效参数!");
        if(loc.m_node->m_prev)
            loc.m_node->m_prev->m_next = loc.m_node->m_next;
        else
            m_head = loc.m_node->m_next;
        if(loc.m_node->m_next)
            loc.m_node->m_next->m_prev = loc.m_node->m_prev;
        else
            m_tail = loc.m_node->m_prev;
        node* next = loc.m_node->m_next;
        delete loc.m_node;
        return iterator(m_head,m_tail,next);
    }
    //常正向迭代器
    /**
     * 考虑这里可以用继承，我们一般都是用公有继承，公有继承的语义是：子类即是基类
     * 假设使用公有继承，子类也是基类，也就是说常迭代器也是迭代器，但是迭代器
     * 是可以写的，常迭代器不可以写，语义上是不通的。
     * 使用私有继承，所有在基类中实现的函数在子类中都变成私有的了。
     * 私有化以后，外部是不能访问的。同样还要实现一次放在public中，这样就没有继承性了。
     * 所以，我们最好不要用继承。
     * 用公有继承的话，还有一个矛盾：可以把常迭代器隐式的转换成迭代器了，就好像可以把一个
     * 常指针隐式转换成普通指针一样，这么做编译器肯定是不允许的，编译器不会让你把一个
     * 常指针隐式的转换成普通指针，这样和指针的语法是不一致的。
     * 所以我们不使用继承模型，而使用混合模型，就是在常迭代器内部封装（定义）一个普通迭代器，
     * 因为从物理结构上看，这种成员组合模型和继承组合模型是一样的，只不过继承组合模型是
     * 基类子对象，而成员组合模型是成员子对象，都可以体现封装的封装，
     * 但是在逻辑模型上，它们是不一样的，因为成员组合模型不再受继承的约束，不再受子类继承
     * 基类这种限制，也不用考虑私有继承这套麻烦事了。
     */
    class const_iterator{
    public:
        /**
         * 首先，在类里不提供任何的构造函数的时候，系统会默认提供一个无参公有构造，如果
         * 自己定义了构造函数，无论有参无参，系统都会收回自己的无参构造。
         * 这里定义一个无参构造，什么都不用做，这样，当定义一个const_iterator的对象，
         * 并且什么参数都不提供，就会调用这里的无参构造，调用无参构造的好处就是会用
         * 默认值去初始化成员，这里的指针会被初始化成NULL（m_it里的成员变量初始化为
         * 空指针）
         */
        const_iterator(){}
        //类型转换构造函数，因为一个普通指针可以隐式的转换成常量指针
        const_iterator(const iterator& it):m_it(it){}
        bool operator==(const const_iterator it)const{
            return m_it == it.m_it;
        }
        bool operator!=(const const_iterator it)const{
            return !(*this == it);
        }
        //前++
        const_iterator& operator++(){
            ++m_it;
            return *this;
        }
        //后++
        const const_iterator operator++(int){
            const_iterator old = *this;
            ++*this;
            return old;
        }
        const_iterator& operator--(){
            --m_it;
            return *this;
        }
        const const_iterator operator--(int){
            const_iterator old = *this;
            --*this;
            return old;
        }
        //返回值是否用引用：返回一个副本还是返回值本身。
        //返回的是一个右值，常引用，不可以改
        const T& operator*()const{
            return *m_it;
        }
        const T* operator->()const{
            return &**this;
        }
    private:
        iterator m_it;
    };
    //获取起始常正向迭代器
    //常容器对应的迭代器必定是具有常属性的，不然，容器的常属性就没有意义
    const_iterator begin()const{
        //普通的迭代器可以隐式的转换成常迭代器，因为我们有类型转换构造函数
        return const_cast<list*>(this)->begin();
    }
    //获取终止常正向迭代器
    const_iterator end()const{
        //普通的迭代器可以隐式的转换成常迭代器，因为我们有类型转换构造函数
        return const_cast<list*>(this)->end();
    }
    //反向迭代器，对获取的迭代器做++,是向首部移动，--是向尾部移动
    class reverse_iterator{};
    //获取最后一个元素的迭代器
    reverse_iterator rbegin(){};
    //获取第一个元素前面的那个元素的迭代器
    reverse_iterator rend(){};
    //常反向迭代器
    class const_reverse_iterator{};
    const_reverse_iterator rbegin()const{};
    const_reverse_iterator rend()const{};
};
//判等函数针对const char*的特化版本
template<>
/**
 * const char*在通用版本中对应T,也就是某种类型的常引用,也就是说它的目标是不可修改的
 * 特化以后就应该变成一个const char*的常引用,也就是说应该引用一个不可修改的const char*
 * 应该把const写在const char*后面,常量指针常量(指针本身不可修改,它的目标也不可修改),
 * 常量型的常量指针
 * const char* const(判断类型,先看右边再看左边,也就是右优先)
 */ 
bool list<const char*>::equal(const char* const& a,const char* const& b)const{
    return strcmp(a,b) == 0;
}
/**
 * 只通过main函数根本就看不出来list是一个链表（看不到node节点）
 * 因为所有的链表的特征（前后指针，已经被iterator封装起来了）都隐藏在类的实现内部。
 * 就算内部结构是数组，main函数一点都不用动，只不过list类内部的实现要变了。
 * 这样我们就可以用相同的方式来操作不同的迭代器，由此所得到的算法将是泛型（什么类型都可以）。
 * 也就是说对于用户而言，内部结构是透明的。
 */
int main(){
    list<int> list1;
    list1.push_back(50);
    list1.push_back(60);
    list1.push_back(70);
    list1.push_front(40);
    list1.push_front(30);
    list1.push_front(20);
    cout << list1 << endl;//20 30 40 50 60 70 
    list1.pop_front();
    list1.pop_back(); 
    cout << list1 << endl;//30 40 50 60 
    ++list1.front();
    list1.back() -= 20;
    cout << list1 << endl;//31 40 50 40 
    list1.remove(40);
    cout << list1 << endl;//31 50
    const list<int>& clist = list1;
    //clist.front() = 100;
    //clist.back() = 200;
    cout << list1.size() << endl;
    cout << boolalpha << list1.empty() << endl;
    list1.clear();
    cout << boolalpha << list1.empty() << endl;
    cout << list1 << endl;
    char sa[][256] = {"beijing","shanghai","tianjin","shanghai","chongqing"};
    //list<string> list2;
    list<const char*> list2;
    for(size_t i = 0; i < sizeof(sa)/sizeof(sa[0]);i++)
        list2.push_back(sa[i]);
    cout << list2 << endl;
    /**
     * 这里的=是初始化运算符，不是赋值运算符
     * 所以在这里只会发生拷贝构造，不会发生拷贝赋值
     */
    //list<string> list3 = list2; //拷贝构造 等同于list<string> list3(list2);
    list<const char*> list3 = list2; //拷贝构造 等同于list<string> list3(list2);
    list3.pop_front();
    cout << list3 << endl;//s t s c
    cout << list2 << endl;//b s t s c
    //拷贝赋值,显然前面已经构造完了，这个是赋值运算符
    list3 = list2;
    list2.pop_back();
    cout << list3 << endl;//b s t s c
    cout << list2 << endl;//b s t s
    /**
     * const char*去实例化list<>，在remove中比较的时候，一个(容器中)地址在栈里，一个在
     * 代码段，肯定是不一样的
     */
    list3.remove("shanghai");
    /**
     * 前面如果用const char*去实例化list<>的话，list3.remove("shanghai")是无法
     * 将shanghai删掉的。
     */
    cout << list3 << endl;// b t c
    /**
     * 这样遍历的过程中，没有用到node,next之类的，只是用了iterator迭代器。迭代器重载了
     * 指针的功能,这样,迭代器就是容器中每一个数据元素的指针
     * const char*类型的不能用->,因为用->无法取到字符串的地址，而是字符串首地址的地址
     */
    for(list<const char*>::iterator it=list3.begin();it!=list3.end();++it)
        cout << *it << ' ';
    cout << endl;
    list<string> list4;
    list4.push_back("张飞");
    list4.push_back("赵云");
    list4.push_back("关羽");
    for(list<string>::iterator it = list4.begin();it != list4.end();++it)
        cout << it->c_str() << ' ';
    cout << endl;
    list<string>::iterator it = list4.begin();
    it = list4.insert(it,"曹操");
    cout << *it << endl;
    cout << list4 << endl;
    it = list4.end();
    it = list4.insert(it,"刘备");
    cout << *it << endl;
    cout << list4 << endl;
    it = list4.begin();
    ++++it;
    it = list4.insert(it,"黄忠");
    cout << *it << endl;
    cout << list4 << endl;
    it = list4.begin();
    ++it;
    it = list4.erase(it);
    cout << *it << endl;
    cout << list4 << endl;
    /**
     * 这个地方cit相当于指针常量，cit本身不可以修改，但是cit所指向的对象
     * 可以修改，这显然和我们的目标不一致,我们的目标是常量指针，指针所指向的目标
     * 不可以修改
     */
//    const list<string>::iterator cit = list4.begin();//编译器没有报错
//    *cit = "小王";//修改成功
//    cout << list4 << endl;
//    cit++;//报错，常cit不能++
    list<string>::const_iterator cit = list4.begin();
    //常迭代器的*运算符返回的是const T&,右值，不能修改，常迭代器的目标不可修改
//    *cit = "小王";
    cout << *cit << endl;

    return 0;
}
