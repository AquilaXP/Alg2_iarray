#define BOOST_TEST_MODULE test_iarray

#include <map>
#include <set>
#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include "IArray.h"
#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "LinkedArray.h"
#include "SpaceArray.h"
#include "PQueue.h"

void TestAddAndGet( IArray< int >* array )
{
    constexpr size_t size = 1000;
    for( int i = 0; i < size; ++i )
        array->add( i );

    BOOST_CHECK_BITWISE_EQUAL( array->size(), size );

    for( int i = 0; i < size; ++i )
        BOOST_CHECK_BITWISE_EQUAL( array->get( i ), i );
}

void TestAddFirstLastPos( IArray< int >* array )
{
    array->add( -3, 0 );
    constexpr size_t size = 1000;
    for( int i = 0; i < size; ++i )
    {
        array->add( i );
    }
    for( int i = 1; i < size + 1; ++i )
    {
        BOOST_CHECK_BITWISE_EQUAL( array->get( i ), i - 1 );
    }
    array->add( -1, 0 );
    array->add( -2, 1002 );
    BOOST_CHECK_BITWISE_EQUAL( array->size(), size + 3 );
    for( int i = 2; i < size + 2; ++i )
    {
        BOOST_CHECK_BITWISE_EQUAL( array->get( i ), i - 2 );
    }

    BOOST_CHECK_BITWISE_EQUAL( array->get( 0 ), -1 );
    BOOST_CHECK_BITWISE_EQUAL( array->get( 1 ), -3 );
    BOOST_CHECK_BITWISE_EQUAL( array->get( 1002 ), -2 );
}

void TestAddRandomPos( IArray< int >* array )
{
    constexpr size_t size = 1000;
    for( int i = 0; i < size; ++i )
        array->add( i );

    std::map<size_t, int> newItem =
    {
        { 4, 24 },
        { 5, 12 },
        { 51, 25 },
        { 0, 11 },
        { size + 4, 1 }
    };

    for( auto[pos, value] : newItem )
    {
        array->add( value, pos );
    }

    BOOST_CHECK_BITWISE_EQUAL( array->size(), size + newItem.size() );

    int curNum = 0;
    for( int i = 0; i < array->size(); ++i )
    {
        int v = array->get( i );
        if( auto it = newItem.find( size_t(i) ); it != newItem.end() )
        {
            BOOST_CHECK_BITWISE_EQUAL( v, it->second );
        }
        else
        {
            BOOST_CHECK_BITWISE_EQUAL( v, curNum );
            ++curNum;
        }
    }

}

void TestRemoveFirst( IArray< int >* array )
{
    constexpr size_t size = 1000;
    for( int i = 0; i < size; ++i )
        array->add( i );

    for( int i = 0; i < size; ++i )
    {
        array->remove( 0 );
        BOOST_CHECK_BITWISE_EQUAL( array->size(), size - i - 1 );
        for( int j = i + 1, k = 0; j < size; ++j, ++k )
            BOOST_CHECK_BITWISE_EQUAL( array->get( k ), j );
    }
}

void TestRemoveLast( IArray< int >* array )
{
    constexpr size_t size = 1000;
    for( int i = 0; i < size; ++i )
        array->add( i );

    for( int i = 0; i < size; ++i )
    {
        array->remove( array->size() - 1 );
        BOOST_CHECK_BITWISE_EQUAL( array->size(), size - i - 1 );
        for( int j = 0; j < size - i - 1; ++j )
            BOOST_CHECK_BITWISE_EQUAL( array->get( j ), j );
    }
}

void TestRemoveMiddle( IArray< int >* array )
{
    constexpr size_t size = 1000;
    std::set< int > values;
    for( int i = 0; i < size; ++i )
    {
        array->add( i );
        values.insert( i );
    }

    for( int i = 0; i < size/2; ++i )
    {
        values.erase( array->remove( array->size() / 2 ) );
        BOOST_CHECK_BITWISE_EQUAL( array->size(), size - i - 1 );
        auto it = values.begin();
        for( int j = 0; j < size - i - 1; ++j, ++it )
        {
            BOOST_CHECK_BITWISE_EQUAL( array->get( j ), *it );
        }
    }
}

#define TEST_IARRAY( type )                                             \
        BOOST_AUTO_TEST_SUITE( test_##type )                            \
                                                                        \
        BOOST_AUTO_TEST_CASE( test_add_get )                            \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestAddAndGet( arr.get() );                                 \
        }                                                               \
        BOOST_AUTO_TEST_CASE( test_add_first_last )                     \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestAddFirstLastPos( arr.get() );                           \
        }                                                               \
        BOOST_AUTO_TEST_CASE( test_add_random_pos )                     \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestAddRandomPos( arr.get() );                              \
        }                                                               \
        BOOST_AUTO_TEST_CASE( test_remove_first )                       \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestRemoveFirst( arr.get() );                               \
        }                                                               \
        BOOST_AUTO_TEST_CASE( test_remove_last )                        \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestRemoveLast( arr.get() );                                \
        }                                                               \
        BOOST_AUTO_TEST_CASE( test_remove_middle )                      \
        {                                                               \
            std::unique_ptr< IArray< int > > arr( new type< int > );    \
            TestRemoveMiddle( arr.get() );                              \
        }                                                               \
                                                                        \
        BOOST_AUTO_TEST_SUITE_END()

TEST_IARRAY( SingleArray )
TEST_IARRAY( VectorArray )
TEST_IARRAY( FactorArray )
TEST_IARRAY( MatrixArray )
TEST_IARRAY( LinkedArray )
TEST_IARRAY( SpaceArray )

BOOST_AUTO_TEST_SUITE( test_PQueue )

BOOST_AUTO_TEST_CASE( test_enqueue )
{
    PQueue< int > pqueue;
    pqueue.enqueue( 10, 0 );
    pqueue.enqueue( 9, 1 );
    pqueue.enqueue( 8, 1 );
    pqueue.enqueue( 7, 9 );
    pqueue.enqueue( 6, 3 );
    pqueue.enqueue( 5, 2 );
    pqueue.enqueue( 4, 5 );

    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 7 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 4 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 6 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 5 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 9 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 8 );
    BOOST_CHECK_BITWISE_EQUAL( pqueue.dequeue(), 10 );
}

BOOST_AUTO_TEST_SUITE_END()
