#pragma once

#include <memory>

#include "SingleArray.h"
#include "VectorArray.h"

template< class T >
class SpaceArray : public IArray< T >
{
public:
    using size_type = IArray< T >::size_type;
    using value_type = IArray< T >::value_type;

    SpaceArray() = default;
    ~SpaceArray()
    {
        clear();
        delete m_data;
    }
    void add( const value_type& item ) override
    {
        if( m_data->size() == 0 )
            m_data->add( new VectorArray< value_type >( m_vector ) );

        if( m_data->get( m_data->size() - 1 )->size() == m_vector )
            m_data->add( new VectorArray< value_type >( m_vector ) );

        m_data->get( m_data->size() - 1 )->add( item );
        ++m_size;
    }
    void add( const value_type& item, size_type index ) override
    {
        if( m_data->size() == 0 )
            m_data->add( new VectorArray< value_type >( m_vector ) );

        size_type index1 = 0;
        size_type index2 = 0;
        if( size() == index )
        {
            if( m_data->get( m_data->size() - 1 )->size() == m_vector )
            {
                m_data->add( new VectorArray< value_type >( m_vector ) );
            }
            index1 = m_data->size() - 1;
            index2 = m_data->get( m_data->size() - 1 )->size();
        }
        else
        {
            std::tie( index1, index2 ) = getIndexes( index );
        }
        if( m_data->get( index1 )->size() == m_vector ||
            m_data->get( index1 )->size() > index2 )
        {
            m_data->add( new VectorArray< value_type >( m_vector ), index1 + 1 );
            auto s = m_data->get( index1 )->size();
            for( size_type i = index2; i < s; ++i )
            {
                m_data->get( index1 + 1 )->add( m_data->get(index1)->remove( index2 ) );
            }
        }
        m_data->get( index1 )->add( item );
        ++m_size;
    }
    value_type remove( size_type index ) override
    {
        value_type removeV = get( index );
        auto[index1, index2] = getIndexes( index );

        m_data->get( index1 )->remove( index2 );
        --m_size;
        if( m_data->get( index1 )->size() == 0 )
        {
            delete m_data->get( index1 );
            m_data->remove( index1 );
        }
        
        return removeV;
    }
    value_type& get( size_type index ) override
    {
        auto[index1, index2] = getIndexes( index );

        return m_data->get( index1 )->get( index2 );
    }
    size_type size() const override
    {
        return m_size;
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
    auto getIndexes( size_type index ) const
    {
        if( index == 0 )
            return std::make_pair( size_t( 0 ), size_t( 0 ) );

        size_type index1 = 0;
        while( m_data->get( index1 )->size() <= index )
        {
            index -= m_data->get( index1 )->size();
            ++index1;
        }
        return std::make_pair( index1, index );
    }

    size_type m_vector = 100;
    size_type m_size = 0;
    IArray< IArray< T >* >* m_data = new SingleArray< IArray< T >* >;
};
