#pragma once

#include "BinarySearchTree.h"
#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:

    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree; // binary search tree
    BTNStack fStack; // DFS traversal stack

    void pushLeft(BTreeNode aNode)
    {
        while (!aNode->empty())
        {
            fStack.push(aNode);
            aNode = aNode->left;
        }
    }

public:

    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTreeIterator(const BSTree& aBSTree) : fBSTree(aBSTree)
    {
        pushLeft(fBSTree.fRoot);
    }

    const T& operator*() const
    {
        return fStack.top()->key;
    }
        
    
    Iterator& operator++()
    {
        if (!fStack.empty())
        {
            BTreeNode currentNode = fStack.top();
            fStack.pop();
            if (!currentNode->right->empty())
            {
                BTreeNode nextNode = currentNode->right;
                while (!nextNode->empty())
                {
                    fStack.push(nextNode);
                    nextNode = nextNode->left;
                }
            }
            return *this;
        }
        else
        {
            throw std::domain_error("Stack is empty.");
        }
    }
    
    Iterator operator++(int)
    {
        Iterator Temp = *this;
        fStack.pop();
        return Temp;
    }
    
    bool operator==(const Iterator& aOtherIter) const
    {
        return (fStack == aOtherIter.fStack) && (fBSTree.fRoot == aOtherIter.fBSTree.fRoot);
    }
    

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

    Iterator begin() const
    {
        Iterator Temp = *this;
        BTNStack Stack;
        Temp.fStack = Stack;
        Temp.pushLeft(Temp.fBSTree.fRoot);
        return Temp;
    }

    Iterator end() const
    {
        Iterator Temp = *this;
        BTNStack Stack;
        Temp.fStack = Stack;
        return Temp;
    }
};
