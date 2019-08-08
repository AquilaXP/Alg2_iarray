#pragma once

#pragma once

#include <algorithm>

#include "IArray.h"
#include "VectorArray.h"

template< class Ty >
class MatrixArray : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    MatrixArray() = default;
    MatrixArray( size_type vector )
        : m_vector( vector )
    {
    }
    ~MatrixArray()
    {
        clear();
    }

    size_type size() const override
    {
        return m_size;
    }

    void add( const value_type& item ) override
    {
        if( m_size == m_data->size() * m_vector )
            grow();
        m_data->get( m_data->size() - 1 )->add( item );
        ++m_size;
    }
    void add( const value_type& item, size_type index ) override
    {
        if( m_size == m_data->size() * m_vector )
            grow();

        size_type index1 = index / m_vector;
        size_type index2 = index % m_vector;

        if( m_data->size() > 1 )
        {
            for( size_type i = 0; i < m_data->size() - 1 - index1; ++i )
            {
                value_type v = m_data->get( m_data->size() - i - 2 )->remove( m_vector - 1 );
                m_data->get( m_data->size() - i - 1 )->add( v, 0 );
            }
        }

        m_data->get( index1 )->add( item, index2 );

        ++m_size;
    }
    value_type remove( size_type index ) override
    {
        value_type removeV = get( index );

        size_type index1 = index / m_vector;
        size_type index2 = index % m_vector;

        m_data->get( index1 )->remove( index2 );
        for( size_type i = index1; i < m_data->size() - 1; ++i )
        {
            m_data->get( i )->add( m_data->get( i + 1 )->remove( 0 ) );
        }
        if( m_data->get( m_data->size() - 1 )->size() == 0 )
        {
            delete m_data->get( m_data->size() - 1 );
            m_data->remove( m_data->size() - 1 );
        }

        --m_size;

        return removeV;
    }
    value_type& get( size_type index ) override
    {
        size_type index1 = index / m_vector;
        size_type index2 = index % m_vector;
        return m_data->get(index1)->get(index2);
    }
    void clear() override
    {
        for( size_type i = 0; i < m_data->size(); ++i )
        {
            delete m_data->get( i );
        }
        m_data->clear();
        m_size = 0;
    }
private:
    void grow()
    {
        m_data->add( new VectorArray< value_type >( m_vector ) );
    }

    template< class Ty >
    using puIArray = std::unique_ptr< IArray< Ty > >;

    size_type m_size = 0;
    puIArray< IArray< value_type >* > m_data{ new SingleArray < IArray< value_type >* > };
    size_type m_vector = 100;
};