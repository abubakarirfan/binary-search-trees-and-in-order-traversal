#pragma once

#include "BinaryTreeNode.h"
#include <stdexcept>

// Problem 3 requirement
template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    BTreeNode fRoot;

public:

    BinarySearchTree() :fRoot(&BNode::NIL)
    {}

    ~BinarySearchTree()
    {      
        if(!fRoot->empty())
            delete fRoot;
    }

    bool empty() const
    {
        return fRoot->empty();
    }

    size_t height() const
    {
        if(empty())
            throw std::domain_error("Empty tree has no height.");
        else
            return fRoot->height();
    }

    bool insert(const T& aKey)
    {
        if (empty())
            return fRoot = new BNode(aKey);
        fRoot->insert(aKey);
    }

    bool remove(const T& aKey)
    {
        if (fRoot->empty())
        {
            fRoot = &BNode::NIL;
        }
        
        return fRoot->remove(aKey, fRoot);
    }
    

    // Problem 3 methods

    using Iterator = BinarySearchTreeIterator<T>;
    // Allow iterator to access private member variables
    friend class BinarySearchTreeIterator<T>;

    Iterator begin() const
    {
        Iterator Temp = *this;
        return Temp.begin();
    }
    Iterator end() const
    {
        Iterator Temp = *this;
        return Temp.end();
    }
};
