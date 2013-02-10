#include <iostream>

#include "PackedPool.h"
#include "HandledPool.h"

using namespace Data;

void PackedPoolTest()
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
        std::cout<< "PackedPool: " << *iter << std::endl;
    }
}

void HandledPoolTest()
{
    typedef HandledPool< int > ThisPoolType;
    ThisPoolType muhPool;

    // Example values
    int vals[ 3 ];
    for( int i = 0; i < 3; ++i )
        vals[ i ] = i;

    // Add them to get handles (the handles match the numbers so we're ignoring them)
    for( int i = 0; i < 3; ++i ) {
        muhPool.Add( &vals[ i ] );
    }
    
    // Print
    for( int i = 0; i < 5; ++i ) {
        std::cout<< "HandledPool: handle = " << i;
        if( muhPool.ValidHandle( i ) ) {
            std::cout<< " is valid:  Value = " << *( muhPool.ResolveHandle( i ) );
        }
        else {
            std::cout<< " INVALID";
        }

        std::cout<< std::endl;
    }

    // Remove one in the middle
    muhPool.Remove( 1 );

    // Print again
    for( int i = 0; i < 5; ++i ) {
        std::cout<< "HandledPool: handle = " << i;
        if( muhPool.ValidHandle( i ) ) {
            std::cout<< " is valid:  Value = " << *( muhPool.ResolveHandle( i ) );
        }
        else {
            std::cout<< " INVALID";
        }

        std::cout<< std::endl;
    }


}

int main( int argc, const char * argv[] )
{
    PackedPoolTest();
    HandledPoolTest();

    return 0;
}

