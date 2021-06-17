/*
 * =====================================================================================
 *
 *       Filename:  BinaryTree.h
 *
 *    Description:  Abstract class binary tree, abstract data type specification for binary trees, all methods are pure virtual functions
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时25分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CaoRui,
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BinaryTree_H
#define BinaryTree_H

#include <functional>

using namespace std;

template<typename T>
class BinaryTree {
public:
    virtual ~BinaryTree() = default;

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    // parameter is a pointer to a function whose return type is void and has a single argument of type ``T *``
    virtual void preOrder(void (*)(T *)) = 0;

    virtual void inOrder(void (*)(T *)) = 0;

    virtual void postOrder(void (*)(T *)) = 0;

    virtual void levelOrder(void (*)(T *)) = 0;
};

#endif
