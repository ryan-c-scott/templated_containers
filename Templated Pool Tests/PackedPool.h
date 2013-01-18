#ifndef Templated_Pool_Tests_PackedPool_h
#define Templated_Pool_Tests_PackedPool_h

#include <vector>

namespace Data
{

    /// @brief A simple pool approach using an object count only.  Objects off the end are copied into freed slots
    /// One thing I don't like about this is the fact that using this for, as an example, update order makes it such that Erase() changes the order of objects
    /// (i.e. an object that's newer than others could end up being updated before older objects).
    /// It's not a good idea to rely on that in general, so this shouldn't be a problem, but almost arbitrarily swapping order seems nasty.

    template < typename T >
        class PackedPool
    {
        std::vector< T > mPool;
    
    public:

        typedef typename std::vector< T >::iterator iterator;

        PackedPool() {}

        void Add( T val )
        {
            mPool.push_back( val );
        }

        iterator Remove( unsigned idx )
        {
            // Just a wrapper to erase that uses an index
            return Erase( mPool.begin() + idx );
        }

        iterator Erase( iterator iter )
        {
            *iter = *( mPool.end() - 1 );
            mPool.pop_back();

            return iter; // because of the copy there's no shift and the same iterator should be valid.
        }

        iterator begin() { return mPool.begin(); }
        iterator end() { return mPool.end(); }

    };

} // end namespace

#endif
