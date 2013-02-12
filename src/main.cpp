#include <iostream>

#include "packed_pool.h"
#include "pointer_handle_pool.h"

// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* pName, int flags,
    unsigned debugFlags, const char* file, int line)
{
    return malloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
    const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
    // this allocator doesn't support alignment
    EASTL_ASSERT(alignment <= 8);
    return malloc(size);
}

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
    #ifdef _MSC_VER
        return _vsnprintf(pDestination, n, pFormat, arguments);
    #else
        return vsnprintf(pDestination, n, pFormat, arguments);
    #endif
}


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

void PointerHandlePoolTest()
{
    typedef PointerHandlePool< int > ThisPoolType;
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
        std::cout<< "PointerHandlePool: handle = " << i;
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
        std::cout<< "PointerHandlePool: handle = " << i;
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
    PointerHandlePoolTest();

    return 0;
}

