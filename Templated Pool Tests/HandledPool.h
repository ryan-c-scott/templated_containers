#ifndef Templated_Pool_Tests_HandledPool_h
#define Templated_Pool_Tests_HandledPool_h

#include <vector>

namespace Data
{

    template < typename T >
        class HandledPool
    {
        std::vector< T* > mPool;
        std::vector< unsigned > mFreeList;
    
    public:

        // Note: An initial capacity would be nice
        HandledPool() {}

        void Add( T *val )
        {
            if( mFreeList.empty() ) {
                mPool.push_back( val );
            }
            else {
                unsigned freeSlot = mFreeList.back();
                mFreeList.pop_back();
                mPool[ freeSlot ] = val;
            }
        }

        bool ValidHandle( unsigned handle )
        {
            return handle > mPool.begin() && handle < mPool.end() && mPool[ handle ] != NULL;
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
            }

            return ret;
        }

    };

} // end namespace

#endif
