#pragma once

template< class T >
class Node
{
public:
    Node( const T& item, Node< T >* next = nullptr )
        : m_next(next), m_item( item )
    {
    }
    T& getItem()
    {
        return m_item;
    }
    Node< T >* getNext()
    {
        return m_next;
    }
    void setNext( Node< T >* next )
    {
        m_next = next;
    }
private:
    Node< T >* m_next = nullptr;
    T m_item;
};
