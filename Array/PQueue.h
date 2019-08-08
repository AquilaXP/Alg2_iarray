#pragma once

#include "Queue.h"
#include "VectorArray.h"

template< class T >
class PQueue
{
public:
    using size_type = size_t;
    using value_type = T;
    using priority_type = size_t;

    PQueue( priority_type max_priority = 10 )
    {
        m_data = new VectorArray< Queue< value_type >* >( max_priority + 1 );
        for( size_type i = 0; i < max_priority + 1; ++i )
        {
            m_data->add( new Queue< value_type > );
        }
    }
    ~PQueue()
    {
        for( size_type i = 0; i < m_data->size(); ++i )
        {
            delete m_data->get( i );
        }
        delete m_data;
    }
    void enqueue( const value_type& item, priority_type priority = 0 )
    {
        m_data->get( priority )->enqueue( item );
        if( m_last < priority )
            m_last = priority;
    }
    value_type dequeue()
    {
        value_type item = m_data->get( m_last )->dequeue();
        while( m_last > 0 && m_data->get(m_last)->isEmpty() )
        {
            --m_last;
        }
        return item;
    }
    bool isEmpty() const
    {
        return m_size == 0;
    }
private:
    size_type m_size = 0;
    size_type m_last = 0;
    IArray< Queue< value_type >* >* m_data = nullptr;
};