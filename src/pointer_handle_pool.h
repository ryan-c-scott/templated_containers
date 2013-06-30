#pragma once

#include <EASTL/vector.h>

namespace Data
{

    template < typename T >
        class PointerHandlePool
    {
        eastl::vector< T* > _pool;
        eastl::vector< unsigned > _freeList;
        unsigned _size;
    
    public:

        // Note: An initial capacity would be nice
    PointerHandlePool() : _size( 0 ) {}

        unsigned Add( T *val )
        {
            if( _freeList.empty() ) {
                _pool.push_back( val );
                return _size++;
            }
            else {
                unsigned freeSlot = _freeList.back();
                _freeList.pop_back();
                _pool[ freeSlot ] = val;
                return freeSlot;
            }
        }

        bool ValidHandle( unsigned handle )
        {
            return handle < _size && _pool[ handle ] != NULL;
        }

        T* ResolveHandle( unsigned handle )
        {
            if( ValidHandle( handle ) )
                return _pool[ handle ];

            return NULL;
        }

        T* Remove( unsigned handle )
        {
            T* ret = NULL;

            if( ValidHandle( handle ) ) {
                ret = _pool[ handle ];
                _pool[ handle ] = NULL;
                _freeList.push_back( handle );
            }

            return ret;
        }

        void Clear()
        {
            _size = 0;
            _pool.clear();
        }

        unsigned FindHandle( T *objectPtr )
        {
            int i = 0;
            for( typename eastl::vector< T* >::iterator it = _pool.begin(); it != _pool.end(); ++i, ++it ) {
                if( *it == objectPtr )
                    return i;
            }

            return 0;
        }

    };

} // end namespace

