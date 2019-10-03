#pragma once

#include <algorithm>
#include <memory>

#include "IArray.h"

template< class Ty >
class VectorArray : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    VectorArray() = default;
    VectorArray( size_type vector )
        : m_vector(vector)
    {
    }

    VectorArray( const VectorArray< Ty >& other )
    {
        m_data.reset( new value_type[other.m_size] );
        for( size_t i = 0; i < other.m_size; ++i )
            m_data[i] = other.m_data[i];

        m_size = other.m_size;
        m_capacity = m_size;
        m_vector = other.m_vector;
    }
    VectorArray& operator = ( const VectorArray< Ty >& other )
    {
        m_data.reset( new value_type[other.m_size] );
        for( size_t i = 0; i < other.m_size; ++i )
            m_data[i] = other.m_data[i];

        m_size = other.m_size;
        m_capacity = m_size;
        m_vector = other.m_vector;

        return *this;
    }

    size_type size() const override
    {
        return m_size;
    }
    void add( const value_type& item ) override
    {
        if( m_size == m_capacity )
            grow();
        
        m_data[m_size] = item;
        ++m_size;
    }
    void add( const value_type& item, size_type index ) override
    {
        if( m_size == m_capacity )
        {
            size_type new_capacity = m_capacity + m_vector;
            std::unique_ptr< value_type[] > new_array( new value_type[new_capacity] );
            std::move( m_data.get(), m_data.get() + index, new_array.get() );
            new_array[index] = item;
            std::move( m_data.get() + index, m_data.get() + m_size, new_array.get() + index + 1 );
            m_capacity = new_capacity;
            std::swap( m_data, new_array );
        }
        else
        {
            std::move_backward( m_data.get() + index, m_data.get() + m_size, m_data.get() + m_size + 1 );
            m_data[index] = item;
        }
        ++m_size;
    }
    value_type remove( size_type index ) override
    {
        value_type remove_v = std::move( m_data[index] );
        std::move( m_data.get() + index + 1, m_data.get() + m_size, m_data.get() + index );
        --m_size;

        return remove_v;
    }
    value_type& get( size_type index ) override
    {
        return m_data[index];
    }
    void clear() override
    {
        m_data.reset( new value_type[0] );
        m_size = 0;
        m_capacity = 0;
    }
private:
    void grow()
    {
        std::unique_ptr< value_type[] > new_array = nullptr;
        auto newCapacity = m_capacity + m_vector;
        new_array.reset( new value_type[newCapacity] );
        std::move( m_data.get(), m_data.get() + m_size, new_array.get() );
        m_capacity = newCapacity;
        std::swap( m_data, new_array );
    }

    std::unique_ptr< value_type[] > m_data{ new value_type[0] };
    size_type m_size = 0;
    size_type m_capacity = 0;
    size_type m_vector = 100;
};