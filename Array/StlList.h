#pragma once

#include <list>

#include "IArray.h"

template< class Ty >
class StlList : public IArray< Ty >
{
public:
    using size_type = IArray< Ty >::size_type;
    using value_type = IArray< Ty >::value_type;

    StlList() = default;

    void add( const value_type& item ) override
    {
        m_data.push_back( item );
    }
    void add( const value_type& item, size_type index ) override
    {
        auto it = m_data.begin();
        std::advance( it, index );
        m_data.insert( it, item );
    }
    value_type remove( size_type index ) override
    {
        auto it = m_data.begin();
        std::advance( it, index );
        value_type remove_v = std::move( *it );
        m_data.erase( it );

        return remove_v;
    }
    value_type& get( size_type index ) override
    {
        auto it = m_data.begin();
        std::advance( it, index );
        return *it;
    }
    size_type size() const override
    {
        return m_data.size();
    }
    void clear() override
    {
        m_data.clear();
    }

private:
    std::list< Ty > m_data;
};
