#pragma once

#include <algorithm>
#include <memory>

#include "IArray.h"

template< class Ty >
class FactorArray : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    FactorArray() = default;
    FactorArray( size_type factor )
        : m_factor( factor )
    {
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
            auto new_capacity = getGrowCapacity();
            std::unique_ptr< value_type[] > new_array( new value_type[new_capacity] );
            new_array[index] = item;
            std::move_backward( m_data.get() + index, m_data.get() + m_size, new_array.get() + m_size + 1 );
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
    value_type remove( size_type index )
    {
        value_type removeV = std::move( m_data[index] );

        std::move( m_data.get() + index + 1, m_data.get() + m_size, m_data.get() + index );
        --m_size;

        return removeV;
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
        size_type new_capacity = getGrowCapacity();
        std::unique_ptr< value_type[] > new_array( new value_type[new_capacity] );
        std::move( m_data.get(), m_data.get() + m_size, new_array.get() );
        m_capacity = new_capacity;
        std::swap( m_data, new_array );
    }
    size_type getGrowCapacity() const
    {
        return ( m_capacity == 0 ) ? size_type( 1 ) : size_type( m_capacity + m_capacity * m_factor / 100.0 );
    }

    std::unique_ptr< value_type[] > m_data{ new value_type[0] };
    size_type m_size = 0;
    size_type m_capacity = 0;
    size_type m_factor = 100;
};