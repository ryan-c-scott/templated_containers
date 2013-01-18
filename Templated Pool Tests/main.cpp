#include <iostream>

#include "PackedPool.h"

using namespace Data;

template< class T >
void PrintPool( PackedPool< T > pool )
{
    for( typename PackedPool< T >::iterator iter = pool.begin(); iter != pool.end(); ++iter ) {
        std::cout<< ": " << *iter << std::endl;
    }
}

int main( int argc, const char * argv[] )
{
    typedef PackedPool< int > ThisPoolType;

    ThisPoolType muhPool;

    //PrintPool< PackedPool< int > >( muhPool );

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

