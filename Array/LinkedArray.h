#pragma once

#include "IArray.h"
#include "Node.h"

template< class Ty >
class LinkedArray : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    LinkedArray() = default;
    ~LinkedArray()
    {
        clear();
    }

    void add( const value_type& item ) override
    {
        Node< value_type >* node = new Node< value_type >( item );
        if( size() == 0 )
        {
            m_head = m_tail = node;
        }
        else
        {
            m_tail->setNext( node );
            m_tail = node;
        }
        ++m_size;
    }
    void add( const value_type& item, size_type index ) override
    {
        if( index == 0 )
        {
            Node< value_type >* node = new Node< value_type >( item );
            if( size() == 0 )
            {
                m_head = m_tail = node;
            }
            else
            {
                node->setNext( m_head );
                m_head = node;
            }
        }
        else
        {
            Node< value_type >* head = m_head;
            Node< value_type >* prev = nullptr;
            for( size_type i = 0; i < index; ++i )
            {
                prev = head;
                head = head->getNext();
            }
            Node< value_type >* newNode = new Node<value_type>( item, head );
            prev->setNext( newNode );
        }
        ++m_size;
    }
    value_type remove( size_type index ) override
    {
        Node< value_type >* remove_node = m_head;
        Node< value_type >* prev_node = nullptr;
        for( size_type i = 0; i < index; ++i )
        {
            prev_node = remove_node;
            remove_node = remove_node->getNext();
        }
        
        value_type remove_v = remove_node->getItem();
        if( prev_node )
        {
            prev_node->setNext( remove_node->getNext() );
        }
        else
        {
            m_head = remove_node->getNext();
        }
        delete remove_node;
        --m_size;
        return remove_v;
    }
    value_type& get( size_type index ) override
    {
        Node< value_type >* head = m_head;
        for( size_type i = 0; i < index; ++i )
        {
            head = head->getNext();
        }
        return head->getItem();
    }
    size_type size() const override
    {
        return m_size;
    }
    void clear() override
    {
        while( size() != 0 )
            remove( 0 );
        m_size = 0;
    }
private:
    Node< value_type >* m_head = nullptr;
    Node< value_type >* m_tail = nullptr;
    size_type m_size = 0;
};