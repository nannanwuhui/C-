#include <iostream>
#include "builder.h"
using namespace std;


void ConcreateBuilder1::BuilderPartA()
{
    cout << " BuilderPartA by ConcreateBuilder1" << endl;
}

void ConcreateBuilder1::BuilderPartB()
{
    cout << " BuilderPartB by ConcreateBuilder1" << endl;
}


void ConcreateBuilder2::BuilderPartA()
{
    cout << " BuilderPartA by ConcreateBuilder2" << endl;
}

void ConcreateBuilder2::BuilderPartB()
{
    cout << " BuilderPartB by ConcreateBuilder2" << endl;
}


Director::Director(Builder *pBuilder)
    :m_pBuilder(pBuilder)
{

}

Director::~Director()
{
    delete m_pBuilder;
    m_pBuilder = NULL;
}
// Construct 函数表示一个对象的整个构建过程,不同的部分之间的装配方式都是一致的,
// 首先构建 PartA 其次是 PartB,只是根据不同的构建者会有不同的表示
void Director::Construct()
{
    m_pBuilder->BuilderPartA();
    m_pBuilder->BuilderPartB();
}


