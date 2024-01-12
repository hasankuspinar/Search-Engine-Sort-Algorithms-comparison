//
// Created by Hasan on 8.11.2023.
//

//#include "BinarySearchTree.h"
#include <string>
#include <iostream>
using namespace std;
string not_found = "item not found";
template <class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    root = NULL;
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::insert(const Key &x, const Value &y, BSTNode<Key,Value> *&t) const
{
    if ( t == NULL )
        t = new BSTNode<Key,Value>( x, y, NULL, NULL );

    else if ( x < t->key ) {
        // X should be inserted to the left tree!
        insert( x, y, t->left );
    }
    else if( t->key < x )
    {    // Otherwise X is inserted to the right subtree
        insert( x, y, t->right );
    }
    else
        ;  // Duplicate; do nothing


}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::keyAt(BSTNode<Key,Value> *t) const
{
    if(t != NULL)
    {
        return t->key;
    }
    return not_found;
}

template <class Key, class Value>
Value & BinarySearchTree<Key,Value>::valueOf(Key key) //returns the value object of the tree for the given key
{
    BSTNode<Key, Value> *temp;
    temp = find(key, root);
    return temp->value;
}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::find(const Key &x) const
{
    return keyAt( find( x, root ) );
}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::findMin() const
{
    return keyAt( findMin( root ) );
}

template <class Key, class Value>
BSTNode<Key,Value> * BinarySearchTree<Key,Value>::findMin(BSTNode<Key, Value> *t) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Key, class Value>
const Key & BinarySearchTree<Key,Value>::findMax() const
{
    return keyAt(findMax(root));
}

template <class Key, class Value>
BSTNode<Key,Value> * BinarySearchTree<Key,Value>::findMax(BSTNode<Key, Value> *t) const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;

}

template <class Key, class Value>
BSTNode<Key,Value> * BinarySearchTree<Key,Value>::find(const Key &x, BSTNode<Key,Value> *t) const
{
    if ( t == NULL )
        return NULL;
    else if( x < t->key )
        return find( x, t->left );
    else if( t->key < x )
        return find( x, t->right );
    else
        return t;    // Match
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::insert(const Key &x, const Value &y)
{
    insert(x,y, root);
}

template <class Key, class Value>
bool BinarySearchTree<Key,Value>::isEmpty() const
{
    return root == NULL;
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::makeEmpty()
{
    makeEmpty(root);
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::makeEmpty(BSTNode<Key, Value> *&t) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template <class Key, class Value>
BinarySearchTree<Key,Value>::~BinarySearchTree()
{
    makeEmpty();
}

template <class Key,class Value>
BSTNode<Key,Value> * BinarySearchTree<Key,Value>::clone(BSTNode<Key, Value> *t) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BSTNode<Key,Value>( t->key, t->value, clone( t->left ), clone( t->right ));
}

template<class Key, class Value>
BinarySearchTree<Key,Value>::BinarySearchTree(const BinarySearchTree<Key, Value> &rhs)
{
    makeEmpty();
    root = clone(rhs);
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::remove(const Key &x)
{
    remove(x,root);
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::remove(const Key &x, BSTNode<Key, Value> *&t) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if (x < t->key)
    {
        remove(x, t->left);
    }
    else if( t->key < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->key = findMin( t->right )->key;
        t->value = findMin(t->right)->value;
        remove( t->key, t->right );
    }
    else // one or no children
    {
        BSTNode<Key,Value> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

template <class Key, class Value>
void BinarySearchTree<Key,Value>::printTree() const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}

template <class Key, class Value>
void BinarySearchTree<Key, Value>::printTree(BSTNode<Key, Value> *t) const
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->key << endl;
        printTree( t->right );
    }
}

template <class Key, class Value>
int BinarySearchTree<Key,Value>::calculateSize()
{
    calculateSize(root);
}

template <class Key, class Value>
int BinarySearchTree<Key, Value>::calculateSize(BSTNode<Key, Value> *t)
{
    if(t == NULL)
    {
        return 0;
    }

    return 1 + calculateSize(t->left) + calculateSize(t->right);
}


