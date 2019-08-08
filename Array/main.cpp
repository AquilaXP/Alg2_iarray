#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#include "SingleArray.h"
#include "VectorArray.h"
#include "FactorArray.h"
#include "MatrixArray.h"
#include "LinkedArray.h"
#include "SpaceArray.h"
#include "StlList.h"
#include "Stack.h"
#include "Queue.h"
#include "TestIArray.h"

int main()
{
    size_t count = 100000;

    using tiks = std::chrono::milliseconds;

    TestIArray<tiks> singleArray{ new SingleArray<int>, count };
    TestIArray<tiks> vectorArray{ new VectorArray<int>( 100 ), count };
    TestIArray<tiks> factorArray{ new FactorArray<int>( 100 ), count };
    TestIArray<tiks> matrixArray{ new MatrixArray<int>, count };
    TestIArray<tiks> linkerArray{ new LinkedArray<int>, count };
    TestIArray<tiks> spaceArray{ new SpaceArray<int>, count };
    TestIArray<tiks> stlList{ new StlList<int>, count };

    std::vector< ResultTime > results;

    results.push_back( singleArray.execute() );
    results.push_back( vectorArray.execute() );
    results.push_back( factorArray.execute() );
    results.push_back( matrixArray.execute() );
    results.push_back( linkerArray.execute() );
    results.push_back( spaceArray.execute() );
    results.push_back( stlList.execute() );

    std::ofstream ostr( "res_time.txt" );
    ostr << "all milliseconds, count iteration = " << count << "\n";
    ostr << std::setw( 20 ) << "Name" <<
        std::setw( 12 ) << "insertBegin" <<
        std::setw( 12 ) << "insertRnd" <<
        std::setw( 12 ) << "insertEnd" <<
        std::setw( 12 ) << "readBegin" <<
        std::setw( 12 ) << "readRnd" <<
        std::setw( 12 ) << "readEnd" <<
        std::setw( 12 ) << "removeBegin" <<
        std::setw( 12 ) << "removeRnd" <<
        std::setw( 12 ) << "removeEnd" << '\n';

    for( auto& r : results )
    {
        ostr << std::setw( 20 ) << r.name_cont <<
            std::setw( 12 ) << r.insert.begin <<
            std::setw( 12 ) << r.insert.random <<
            std::setw( 12 ) << r.insert.end <<
            std::setw( 12 ) << r.read.begin <<
            std::setw( 12 ) << r.read.random <<
            std::setw( 12 ) << r.read.end <<
            std::setw( 12 ) << r.remove.begin <<
            std::setw( 12 ) << r.remove.random <<
            std::setw( 12 ) << r.remove.end << '\n';
    }

    return 0;
}
