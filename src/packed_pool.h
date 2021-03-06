#pragma once

#include <EASTL/vector.h>

namespace Data
{

    /// @brief A simple pool approach using an object count only.  Objects off the end are copied into freed slots
    /// One thing I don't like about this is the fact that using this for, as an example, update order makes it such that Erase() changes the order of objects
    /// (i.e. an object that's newer than others could end up being updated before older objects).
    /// It's not a good idea to rely on that in general, so this shouldn't be a problem, but almost arbitrarily swapping order seems nasty.

    template < typename T >
        class PackedPool
    {
        eastl::vector< T > _pool;
    
    public:

        typedef typename eastl::vector< T >::iterator iterator;

        PackedPool() {}

        void Add( T val )
        {
            _pool.push_back( val );
        }

        iterator Remove( unsigned idx )
        {
            // Just a wrapper to erase that uses an index
            return Erase( _pool.begin() + idx );
        }

        iterator Erase( iterator iter )
        {
            *iter = *( _pool.end() - 1 );
            _pool.pop_back();

            return iter; // because of the copy there's no shift and the same iterator should be valid.
        }

        iterator begin() { return _pool.begin(); }
        iterator end() { return _pool.end(); }

    };

} // end namespace

