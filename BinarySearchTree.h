//
// Created by Hasan on 8.11.2023.
//

#ifndef CS300HW2_BINARYSEARCHTREE_H
#define CS300HW2_BINARYSEARCHTREE_H

template <class Key, class Value>
struct BSTNode
{
    Key key;
    Value value;
    BSTNode   		*left;
    BSTNode   		*right;

    BSTNode( const Key & theKey, const Value & theValue,
             BSTNode *lt, BSTNode *rt)
            : key( theKey ),value( theValue ), left( lt ), right( rt ) { }

};
template <class Key, class Value>
class BinarySearchTree
{
private:
    BSTNode<Key,Value> * root;

    const Key & keyAt( BSTNode<Key,Value> *t ) const;

    void insert( const Key & x, const Value & y, BSTNode<Key,Value> * & t ) const;
    void remove(const Key & x, BSTNode<Key,Value> * & t ) const;

    BSTNode<Key,Value> * findMin( BSTNode<Key,Value> *t ) const;
    BSTNode<Key,Value> * findMax( BSTNode<Key,Value> *t ) const;
    BSTNode<Key,Value> * find( const Key & x, BSTNode<Key,Value> *t )const;
    void makeEmpty( BSTNode<Key,Value> * & t ) const;
    BSTNode<Key,Value> * clone( BSTNode<Key,Value> *t ) const;

    void printTree(BSTNode<Key,Value> * t)const;
    int calculateSize(BSTNode<Key,Value> * t);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree & rhs);
    ~BinarySearchTree( );

    void printTree()const;
    const Key & find( const Key & x ) const;
    Value & valueOf( Key key );
    bool isEmpty( ) const;
    const Key & findMin( ) const;
    const Key & findMax( ) const;


    void makeEmpty( );
    void insert( const Key & x , const Value & y);
    void remove( const Key & x );

    int calculateSize();
};




#endif //CS300HW2_BINARYSEARCHTREE_H
#include "BinarySearchTree.cpp"