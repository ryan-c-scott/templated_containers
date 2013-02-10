#include <iostream>

#include "PackedPool.h"
#include "HandledPool.h"

using namespace Data;

int main( int argc, const char * argv[] )
{
    typedef PackedPool< int > ThisPoolType;

    ThisPoolType muhPool;

    for( int i = 0; i < 10; ++i ) {
        muhPool.Add( i );
    }

    muhPool.Remove( 0 );
    muhPool.Remove( 3 );
    muhPool.Remove( 6 );
    muhPool.Remove( 0 );

    muhPool.Remove( 0 );

    for( ThisPoolType::iterator iter = muhPool.begin(); iter != muhPool.end(); ++iter ) {
        std::cout<< ": " << *iter << std::endl;
    }

    return 0;
}

