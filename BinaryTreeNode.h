/*
 * =====================================================================================
 *
 *       Filename:  BinaryTreeNode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时31分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  CaoRui,
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef BinaryTreeNode_H
#define BinaryTreeNode_H

using namespace std;

template<typename T>
struct BinaryTreeNode {
    T element_;
    BinaryTreeNode<T> *left_child_, *right_child_;    // left & right subtree

    BinaryTreeNode() : element_(NULL), left_child_(nullptr), right_child_(nullptr) {}

    explicit BinaryTreeNode(const T &theElement) :
      element_(theElement), left_child_(nullptr), right_child_(nullptr) {}

    BinaryTreeNode(const T &theElement,
                   BinaryTreeNode *theLeftChild,
                   BinaryTreeNode *theRightChild)
      : element_(theElement), left_child_(theLeftChild), right_child_(theRightChild) {}

    ~BinaryTreeNode() = default;
//    ~BinaryTreeNode() {
//        cout << "Destruct BinaryTreeNode!" << endl;
//    }
};


#endif
