#pragma once

template< class Ty >
class IArray
{
public:
    using size_type = size_t;
    using value_type = Ty;

    virtual size_type size() const = 0;
    virtual void add( const value_type& item ) = 0;
    virtual value_type& get( size_type index ) = 0;
    virtual void add( const value_type& item, size_type index ) = 0;
    virtual value_type remove( size_type index ) = 0;
    virtual void clear() = 0;

    virtual ~IArray() = default;
};
