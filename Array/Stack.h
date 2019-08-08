#pragma once

#include <exception>
#include <vector>
#include "Node.h"

template < class T >
class Stack
{
public:
    Stack() = default;

    void push( const T& item )
    {
        m_head = new Node<T>( item, m_head );
    }
    bool isEmpty() const
    {
        return m_head == nullptr;
    }
    T pop()
    {
        T v = m_head->getItem();
        auto prev = m_head->getNext();
        delete m_head;
        m_head = prev;

        return v;
    }
private:
    Node< T >* m_head = nullptr;
};