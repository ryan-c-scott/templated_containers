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
        typedef std::vector< T > PoolType;
        PoolType mPool;
    
    public:
    
    PackedPool() {}

        typedef typename PoolType::iterator iterator;
        
        void Add( T val )
        {
            // Push and increment head
            mPool.push_back( val );
        }

        typename PoolType::iterator Remove( unsigned idx )
        {
            // Just a wrapper to erase that uses an index
            return Erase( mPool.begin() + idx );
        }

        typename PoolType::iterator Erase( typename PoolType::iterator iter )
        {
            // Copy head to this iter and decrement head

            // Need to check that this isn't the last element

            *iter = *( mPool.end() - 1 );
            mPool.pop_back();

            return iter; // because of the copy there's no shift and the same iterator should be valid.
        }
        
        typename PoolType::iterator begin() { return mPool.begin(); }
        typename PoolType::iterator end() { return mPool.end(); }

    };

} // end namespace

#endif
