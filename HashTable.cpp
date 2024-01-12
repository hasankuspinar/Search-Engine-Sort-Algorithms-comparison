//
// Created by Hasan on 9.12.2023.
//
#include <cmath>
#include <string>
//#include "HashTable.h"
#include <iostream>
using namespace std;

WordItem* h_not_found = NULL;

bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;

    return true;
}

int nextPrime( int n )
{
    if ( n % 2 == 0 )
        n++;

    for ( ; ! isPrime( n ); n += 2 )
        ;

    return n;
}


int hash1 ( WordItem  &key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i < key.word.length();i++)
        hashVal = 37 * hashVal + key.word[ i ];

    hashVal = hashVal % tableSize;

    if (hashVal < 0)
        hashVal = hashVal + tableSize;

    return(hashVal);
}


template <class HashedObj>
HashTable<HashedObj>::HashTable(int size )
        : array( nextPrime( size ) )
{
    makeEmpty( );
    currentSize = 0;
}

template <class HashedObj>
void HashTable<HashedObj>::printInfo()
{
    cout << "After preprocessing, the unique word count is " << currentSize << ". Current load ratio is " << ((currentSize*1.0)/array.size()) << endl;
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(  HashedObj & x )
{
    int collisionNum = 0;
    int currentPos = hash1( x, array.size( ) );

    while ( array[ currentPos ].info != EMPTY &&
            array[ currentPos ].element != x )
    {
        currentPos += pow(++collisionNum, 2) ;  //add the difference
        if ( currentPos >= array.size( ) )              // perform the mod
            currentPos = currentPos % array.size( );                // if necessary
    }
    return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos )
{
    return array[ currentPos ].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::remove(  HashedObj & x )
{
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        array[ currentPos ].info = DELETED;
}

template <class HashedObj>
HashedObj* HashTable<HashedObj>::find(  HashedObj & x )
{
    int currentPos = findPos( x );
    if (isActive( currentPos ))
        return &(array[ currentPos ].element);

    return h_not_found;
}

template <class HashedObj>
void HashTable<HashedObj>::insert(  HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        return;
    array[ currentPos ] = HashEntry( x, ACTIVE );

    // enlarge the hash table if necessary
    if ( ++currentSize >= array.size( ) / 1.5 ) {
        rehash();
    }
}

template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for ( int j = 0; j < array.size( ); j++ )
        array[ j ].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
            insert( oldArray[ i ].element );

    //cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: " << currentSize
    //<< ", current load factor: " << ((currentSize*1.0)/array.size()) << endl;
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for(int i = 0; i < array.size(); i++)
    {
        array[i].info = EMPTY;
    }
}



