//
// Created by Hasan on 9.12.2023.
//
#include <vector>
using namespace std;

#ifndef CS300HW3_HASHTABLE_H
#define CS300HW3_HASHTABLE_H

struct DocumentItem {
    string documentName;
    int count;
    bool operator == (const DocumentItem & w) const
    {
        return w.documentName == documentName;
    }

    bool operator != (const DocumentItem & w) const
    {
        return !(w.documentName == documentName);
    }
    bool operator < (const DocumentItem & w) const
    {
        return (documentName < w.documentName);
    }
    bool operator > (const DocumentItem & w) const
    {
        return (documentName > w.documentName);
    }
    bool operator <= (const DocumentItem & w) const
    {
        return (documentName <= w.documentName);
    }
    bool operator >= (const DocumentItem & w) const
    {
        return (documentName >= w.documentName);
    }
};

struct WordItem {
    string word;
    vector<DocumentItem> documentList;

    bool operator == (const WordItem & w) const
    {
        return w.word == word;
    }

    bool operator != (const WordItem & w) const
    {
        return !(w.word == word);
    }
    bool operator < (const WordItem & w) const
    {
        return (word < w.word);
    }
    bool operator > (const WordItem & w) const
    {
        return (word > w.word);
    }
    bool operator <= (const WordItem & w) const
    {
        return (word <= w.word);
    }
    bool operator >= (const WordItem & w) const
    {
        return (word >= w.word);
    }
};
template <class HashedObj>
class HashTable
{
public:
    explicit HashTable( int size );
    HashTable( const HashTable & rhs )
            :array( rhs.array ), currentSize( rhs.currentSize ) { }

    HashedObj* find(  HashedObj & x ) ;

    void makeEmpty( );
    void insert(  HashedObj & x );
    void remove(  HashedObj & x );
    void printInfo();

    const HashTable & operator=( const HashTable & rhs );

    enum EntryType { ACTIVE, EMPTY, DELETED };
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(  HashedObj  e = HashedObj(), EntryType i = EMPTY )
                : element( e ), info( i ) { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) ;
    int findPos(  HashedObj & x ) ;
    void rehash( );
};
int hash1( WordItem  &key, int tableSize);

#endif //CS300HW3_HASHTABLE_H
#include "HashTable.cpp"
