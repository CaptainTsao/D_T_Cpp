/*
 * =====================================================================================
 *
 *       Filename:  BinaryTreeTraversals.cc
 *
 *    Description:  binary tree traversal methods
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 21时12分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CaoRui
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "ArrayQueue.h"
#include "BinaryTreeNode.h"
#include "MyExceptions.h"

using namespace std;

template<typename T>
void visit(BinaryTreeNode<T> *x) {
    /* visit node *x, just output element field */
    cout << x->element_ << ' ';
}

template<typename T>
void PreOrder(BinaryTreeNode<T> *tree) {
    /* pre-order traverse of tree */
    if (tree != nullptr) {
        visit(tree);                        // visit tree root
        PreOrder(tree->left_child_);        // do left sub-tree
        PreOrder(tree->right_child_);       // do right sub-tree
    }
}

template<typename T>
void InOrder(BinaryTreeNode<T> *tree) {
    if (tree != nullptr) {
        InOrder(tree->left_child_);
        visit(tree);
        InOrder(tree->right_child_);
    }
}

template<typename T>
void PostOrder(BinaryTreeNode<T> *tree) {
    if (tree != nullptr) {
        PostOrder(tree->left_child_);
        PostOrder(tree->right_child_);
        visit(tree);
    }
}

template<typename T>
void LevelOrder(BinaryTreeNode<T> *tree) {
    /* Level order traversal of *tree */
    ArrayQueue<BinaryTreeNode<T> *> queue;
    while (tree != nullptr) {
        visit(tree);

        /* put tree's child on queue */
        if (tree->left_child_ != nullptr) {
            queue.push(tree->left_child_);
        }
        if (tree->right_child_ != nullptr) {
            queue.push(tree->right_child_);
        }
        /* get next node to visit */
        try {
            tree = queue.front();
        } catch (QueueEmpty) {
            return;
        }
        queue.pop();
    }
}

int main() {
    /* create a binary tree with root x */
    BinaryTreeNode<int> *x, *y, *z;
    y = new BinaryTreeNode<int>(2);
    z = new BinaryTreeNode<int>(3);
    x = new BinaryTreeNode<int>(1, y, z);

    // traverse x in all ways
    cout << "InOrder sequence is ";
    InOrder(x);
    cout << endl;
    cout << "PreOrder sequence is ";
    PreOrder(x);
    cout << endl;
    cout << "PostOrder sequence is ";
    PostOrder(x);
    cout << endl;
    cout << "LevelOrder sequence is ";
    LevelOrder(x);
    cout << endl;
    cout << "traverse done!" << endl;
    return 0;
}