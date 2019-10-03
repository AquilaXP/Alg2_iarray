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
    value_type& operator [] ( size_type index )
    {
        return get( index );
    }

    virtual ~IArray() = default;
};

template< class Ty >
using pIArray = std::unique_ptr< IArray< Ty > >;

template< class Ty >
using psIArray = std::shared_ptr< IArray< Ty > >;

template< class Ty >
bool operator == ( pIArray< Ty >& lhs, pIArray< Ty >& rhs )
{
    if( lhs->size() != rhs->size() )
        return false;

    for( size_t i = 0; i < lhs->size(); ++i )
    {
        if( !( ( *lhs )[i] == ( *rhs )[i] ) )
            return false;
    }

    return true;
}

template< class Ty >
bool operator != ( pIArray< Ty >& lhs, pIArray< Ty >& rhs )
{
    return !( lhs == rhs );
}

template< class Ty >
bool operator == ( psIArray< Ty >& lhs, psIArray< Ty >& rhs )
{
    if( lhs->size() != rhs->size() )
        return false;

    for( size_t i = 0; i < lhs->size(); ++i )
    {
        if( !( ( *lhs )[i] == ( *rhs )[i] ) )
            return false;
    }

    return true;
}

template< class Ty >
bool operator != ( psIArray< Ty >& lhs, psIArray< Ty >& rhs )
{
    return !( lhs == rhs );
}

template< class Ty >
bool operator == ( IArray< Ty >& lhs, IArray< Ty >& rhs )
{
    if( lhs.size() != rhs.size() )
        return false;

    for( size_t i = 0; i < lhs.size(); ++i )
    {
        if( !(lhs[i] == rhs[i]) )
            return false;
    }

    return true;
}

template< class Ty >
bool operator != ( IArray< Ty >& lhs, IArray< Ty >& rhs )
{
    return !( lhs == rhs );
}

template< class Ty >
bool operator == ( IArray< std::unique_ptr< Ty > >& lhs, IArray< std::unique_ptr< Ty > >& rhs )
{
    if( lhs.size() != rhs.size() )
        return false;

    for( size_t i = 0; i < lhs.size(); ++i )
    {
        if( !( *( lhs[i] ) == *( rhs[i] ) ) )
            return false;
    }

    return true;
}

template< class Ty >
bool operator != ( IArray< std::unique_ptr< Ty > >& lhs, IArray< std::unique_ptr< Ty > >& rhs )
{
    return !( lhs == rhs );
}

template< class Ty >
bool operator == ( IArray< std::shared_ptr< Ty > >& lhs, IArray< std::shared_ptr< Ty > >& rhs )
{
    if( lhs.size() != rhs.size() )
        return false;

    for( size_t i = 0; i < lhs.size(); ++i )
    {
        if( !(*( lhs[i] ) == *( rhs[i] )) )
            return false;
    }

    return true;
}

template< class Ty >
bool operator != ( IArray< std::shared_ptr< Ty > >& lhs, IArray< std::shared_ptr< Ty > >& rhs )
{
    return !( lhs == rhs );
}
