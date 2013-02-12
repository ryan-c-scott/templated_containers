#ifndef DATA_POINTER_HANDLE_POOL_H
#define DATA_POINTER_HANDLE_POOL_H

#include <EASTL/vector.h>

namespace Data
{

    template < typename T >
        class PointerHandlePool
    {
        eastl::vector< T* > mPool;
        eastl::vector< unsigned > mFreeList;
        unsigned mSize;
    
    public:

        // Note: An initial capacity would be nice
    PointerHandlePool() : mSize( 0 ) {}

        unsigned Add( T *val )
        {
            if( mFreeList.empty() ) {
                mPool.push_back( val );
                return mSize++;
            }
            else {
                unsigned freeSlot = mFreeList.back();
                mFreeList.pop_back();
                mPool[ freeSlot ] = val;
                return freeSlot;
            }
        }

        bool ValidHandle( unsigned handle )
        {
            return handle < mSize && mPool[ handle ] != NULL;
        }

        T* ResolveHandle( unsigned handle )
        {
            if( ValidHandle( handle ) )
                return mPool[ handle ];

            return NULL;
        }

        T* Remove( unsigned handle )
        {
            T* ret = NULL;

            if( ValidHandle( handle ) ) {
                ret = mPool[ handle ];
                mPool[ handle ] = NULL;
                mFreeList.push_back( handle );
            }

            return ret;
        }

        void Clear()
        {
            mSize = 0;
            mPool.clear();
        }

        unsigned FindHandle( T *objectPtr )
        {
            int i = 0;
            for( eastl::vector< T* >::iterator it = mPool.begin(); it != mPool.end(); ++i, ++it ) {
                if( *it == objectPtr )
                    return i;
            }

            return 0;
        }

    };

} // end namespace

#endif
