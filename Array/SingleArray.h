#pragma once

#include <algorithm>
#include <memory>

#include "IArray.h"

template< class Ty >
class SingleArray : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    SingleArray() = default;
    ~SingleArray()
    {
        clear();
    }
    size_type size() const override
    {
        return m_size;
    }
    void add( const value_type& item ) override
    {
        std::unique_ptr< value_type[] > new_array( new value_type[m_size + 1] );
        new_array[m_size] = item;
        std::move( m_data.get(), m_data.get() + m_size, new_array.get() );
        std::swap( m_data, new_array );
        m_size += 1;
    }
    void add( const value_type& item, size_type index ) override
    {
        std::unique_ptr< value_type[] > new_array( new value_type[m_size + 1] );
        new_array[index] = item;
        std::move( m_data.get(), m_data.get() + index, new_array.get() );
        std::move( m_data.get() + index, m_data.get() + m_size, new_array.get() + index + 1 );
        std::swap( m_data, new_array );
        m_size += 1;
    }
    value_type remove( size_type index ) override
    {
        value_type removeV = std::move( m_data[index] );
        std::unique_ptr< value_type[] > new_array( new value_type[m_size - 1] );
        std::move( m_data.get(), m_data.get() + index, new_array.get() );
        std::move( m_data.get() + index + 1, m_data.get() + m_size, new_array.get() + index );
        std::swap( m_data, new_array );
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
    }
private:
    std::unique_ptr< value_type[] > m_data{ new value_type[0] };
    size_type m_size = 0;
};