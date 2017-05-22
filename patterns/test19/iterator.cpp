#include <iostream>
#include "iterator.h"



ConcreateAggregate::ConcreateAggregate(int size)
    :m_size(size),m_pdata(NULL)
{
    m_pdata = new int[m_size];
    for(int i = 0;i < m_size;i++){
        m_pdata[i] = i;
    }
}

ConcreateAggregate::~ConcreateAggregate()
{
    delete[] m_pdata;
    m_pdata = NULL;
}

Iterator *ConcreateAggregate::createIterater(Aggregate *pAggregate)
{
    return new ConcreateIterator(this);
}

int ConcreateAggregate::getSize()
{
    return m_size;
}

int ConcreateAggregate::getItem(int index)
{
    if(index < m_size){
        return m_pdata[index];
    }
    else{
        return -1;
    }
}



ConcreateIterator::ConcreateIterator(Aggregate *pAggregate)
    :m_pConcreateAggregate(pAggregate),m_index(0)
{

}

void ConcreateIterator::first()
{
    m_index = 0;
}

void ConcreateIterator::next()
{
    if(m_index < m_pConcreateAggregate->getSize()){
        m_index++;
    }
}

bool ConcreateIterator::isDone()
{
    return m_index == m_pConcreateAggregate->getSize();
}

int ConcreateIterator::currentItem()
{
    return m_pConcreateAggregate->getItem(m_index);
}
