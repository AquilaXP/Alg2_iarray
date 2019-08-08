#pragma once

#include "LinkedArray.h"

template< class T >
class Queue
{
public:
    Queue() = default;

    bool isEmpty() const
    {
        return m_data->size() == 0;
    }
    void enqueue( const T& item )
    {
        m_data->add( item );
    }
    T dequeue()
    {
        return m_data->remove( 0 );
    }
private:
    std::unique_ptr< IArray< T > > m_data{ new LinkedArray< T > };
};
