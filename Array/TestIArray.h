#pragma once

#include <chrono>
#include <typeinfo>
#include <random>
#include <string>

#include "IArray.h"

struct Position
{
    size_t begin = 0;
    size_t random = 0;
    size_t end = 0;
};

struct ResultTime
{
    std::string name_cont;

    Position insert;
    Position read;
    Position remove;
};

template< class AccTimer = std::chrono::milliseconds >
class TestIArray
{
public:
    TestIArray( IArray< int >* arr, size_t count_iteration )
        : m_arr( arr ), m_count_iteration( count_iteration )
    {}
    ~TestIArray()
    {
        delete m_arr;
    }
    ResultTime execute()
    {
        ResultTime result_time;
        result_time.name_cont = GetNameTemplate( typeid( *m_arr ).name() );

        m_random_pos = randomPosInsert( m_count_iteration );
        result_time.insert.begin = insertBegin();
        result_time.insert.random = insertRnd();
        result_time.insert.end = insertEnd();

        m_random_pos = randomPosRead( m_count_iteration );
        fill( m_count_iteration );
        result_time.read.begin = readBegin();
        result_time.read.random = readRnd();
        result_time.read.end = readEnd();

        m_random_pos = randomPosInsert( m_count_iteration );
        std::reverse( m_random_pos.begin(), m_random_pos.end() );
        result_time.remove.begin = removeBegin();
        result_time.remove.random = removeRnd();
        result_time.remove.end = removeEnd();

        return result_time;
    }
private:
    size_t insertBegin()
    {
        m_arr->clear();

        start();
        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->add( int(i), 0 );

        return end();
    }
    size_t insertRnd()
    {
        m_arr->clear();

        start();

        size_t i = 0;
        for( auto& p : m_random_pos )
        {
            i++;
            m_arr->add( int(p), p );
        }

        return end();
    }
    size_t insertEnd()
    {
        m_arr->clear();

        start();
        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->add( int(i) );

        return end();
    }
    size_t readBegin()
    {
        start();
        int sum = 0;
        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->get( 0 );

        return end();
    }
    size_t readEnd()
    {
        start();
        size_t e = m_arr->size() - 1;
        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->get( e );

        return end();
    }
    size_t readRnd()
    {
        start();
        for( auto& p : m_random_pos )
            m_arr->get( p );

        return end();
    }
    size_t removeBegin()
    {
        fill( m_count_iteration );
        start();

        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->remove( 0 );

        return end();
    }
    size_t removeEnd()
    {
        fill( m_count_iteration );
        start();

        for( size_t i = 0; i < m_count_iteration; ++i )
            m_arr->remove( m_count_iteration - i - 1 );

        return end();
    }
    size_t removeRnd()
    {
        fill( m_count_iteration );
        start();

        for( auto& p : m_random_pos )
            m_arr->remove( p );

        return end();
    }

    std::string GetNameTemplate( const std::string& fullName )
    {
        return fullName.substr( 0, fullName.find( '<' ) );
    }

    void fill( size_t count )
    {
        m_arr->clear();
        for( size_t i = 0; i < count; ++i )
            m_arr->add( int(i) );
    }
    std::vector< size_t > randomPosInsert( size_t count )
    {
        std::mt19937_64 gen1( 1 );
        std::vector< size_t > pos( size_t( count ), size_t( 0 ) );
        pos[0] = 0;
        for( size_t i = 1; i < count; ++i )
            pos[i] = std::uniform_int_distribution<size_t>( 0, i )( gen1 );
        return pos;
    }
    std::vector< size_t > randomPosRead( size_t count )
    {
        std::mt19937_64 gen1( 1 );
        std::vector< size_t > pos( size_t( count ), size_t( 0 ) );
        std::uniform_int_distribution<size_t> uid( 0, count );

        for( size_t i = 0; i < count; ++i )
            pos[i] = uid( gen1 );

        return pos;
    }
    void start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    auto end()
    {
        auto e = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<AccTimer>( e - m_start ).count();
    }

    std::vector< size_t > m_random_pos;
    IArray< int >* m_arr = nullptr;
    size_t m_count_iteration = 0;
    std::chrono::high_resolution_clock::time_point m_start;
};
