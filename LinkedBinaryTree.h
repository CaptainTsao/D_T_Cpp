/*
 * =====================================================================================
 *
 *       Filename:  LinkedBinaryTree.h
 *
 *    Description:  linked binary tree using nodes of type BinaryTreeNode derived from the abstract class BinaryTree 
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 20时10分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LinkedBinaryTree_H
#define LinkedBinaryTree_H

#include <iostream>
#include <vector>

#include "BinaryTree.h"
#include "ArrayQueue.h"
#include "BinaryTreeNode.h"
#include "MyExceptions.h"
#include "Booster.h"

using namespace std;

template<typename T>
class Solution;

template<typename T>
class Solution_LevelOrder;

template<typename T>
class LinkedBinaryTree : public BinaryTree<BinaryTreeNode<T>> {
public:
    friend Solution<T>;
    friend Solution_LevelOrder<T>;
public:
    LinkedBinaryTree() : root_(nullptr), tree_size_(0) {}

    LinkedBinaryTree(BinaryTreeNode<T> *root, int tree_size) : root_(root), tree_size_(tree_size) {}

    ~LinkedBinaryTree() {
        erase();
    }

    bool empty() const override {
        return tree_size_ == 0;
    }

    int size() const override {
        return tree_size_;
    }

    T *rootElement() const;

    void makeTree(const T &element,
                  LinkedBinaryTree<T> &,
                  LinkedBinaryTree<T> &);

    LinkedBinaryTree<T> &removeRightSubtree();

    LinkedBinaryTree<T> &removeLeftSubtree();

    void preOrder(void (*theVisit)(BinaryTreeNode<T> *)) {
        visit = theVisit;
        preOrder(root_);
    }

    void inOrder(void (*theVisit)(BinaryTreeNode<T> *)) {
        visit = theVisit;
        inOrder(root_);
    }

    void postOrder(void (*theVisit)(BinaryTreeNode<T> *)) {
        visit = theVisit;
        postOrder(root_);
    }

    void erase() {
        postOrder(dispose);
        root_ = nullptr;
        tree_size_ = 0;
    }

    void levelOrder(void (*theVisit)(BinaryTreeNode<T> *));

    void preOrderOutput() {
        preOrder(output);
        cout << endl;
    }


    void inOrderOutput() {
        inOrder(output);
        cout << endl;
    }


    void postOrderOutput() {
        postOrder(output);
        cout << endl;
    }

    void levelOrderOutput() {
        levelOrder(output);
        cout << endl;
    }

    int height() const {
        return height(root_);
    }

    vector<T> rightSideView(void (*theVisit)(BinaryTreeNode<T> *) = output);

protected:
    BinaryTreeNode<T> *root_;
    int tree_size_;

    void (*visit)(BinaryTreeNode<T> *);  // 访问函数

    static int count_;

    void preOrder(BinaryTreeNode<T> *tree);

    void inOrder(BinaryTreeNode<T> *tree);

    void postOrder(BinaryTreeNode<T> *tree);

    void countNodes(BinaryTreeNode<T> *tree) {
        visit = addToCount;
        count_ = 0;
        preOrder(tree);
    }

    static void dispose(BinaryTreeNode<T> *tree) {
        delete tree;
    }

    static void output(BinaryTreeNode<T> *tree) {
        cout << tree->element_ << ' ';
    }

    static void addToCount(BinaryTreeNode<T> *tree) {
        count_++;
    }

    static int height(BinaryTreeNode<T> *tree);


};

// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
//void (*LinkedBinaryTree<int>::visit)(BinaryTreeNode<int>*);
/* void (*LinkedBinaryTree<Booster>::visit)(BinaryTreeNode<Booster>*); */
/* void (*LinkedBinaryTree<pair<int,int> >::visit)(BinaryTreeNode<pair<int,int> >*); */
/* void (*LinkedBinaryTree<pair<const int,char> >::visit)(BinaryTreeNode<pair<const int,char> >*); */
/* void (*LinkedBinaryTree<pair<const int,int> >::visit)(BinaryTreeNode<pair<const int,int> >*); */



template<typename T>
T *LinkedBinaryTree<T>::rootElement() const {
    // return null if no root, otherwise return pointer to root element 
    if (tree_size_ == 0) {
        return nullptr;
    } else {
        return &this->root_->element_;
    }
}

template<typename T>
void LinkedBinaryTree<T>::makeTree(const T &element, LinkedBinaryTree<T> &left, LinkedBinaryTree<T> &right) {
    root_ = new BinaryTreeNode<T>(element, left.root_, right.root_);
    tree_size_ = left.tree_size_ + right.tree_size_ + 1;

    // deny access from trees from left and right 
    left.root_ = right.root_ = nullptr;
    left.tree_size_ = right.tree_size_ = 0;
}

template<typename T>
LinkedBinaryTree<T> &LinkedBinaryTree<T>::removeLeftSubtree() {
    // remove and return the left subtree 
    // check if empty 
    if (tree_size_ == 0) {
        throw TreeEmpty();
    }

    /* detach left subtree and save in left-subtree */
    LinkedBinaryTree<T> leftSubtree;
    leftSubtree.root_ = root_->left_child_;
    count_ = 0;
    leftSubtree.tree_size_ = countNodes(leftSubtree.root_);
    root_->left_child_ = nullptr;
    tree_size_ -= leftSubtree.tree_size_;

    return leftSubtree;
}


template<typename T>
LinkedBinaryTree<T> &LinkedBinaryTree<T>::removeRightSubtree() {
    // remove and return the left subtree                         
    // check if empty                                             
    if (tree_size_ == 0) {
        throw TreeEmpty();
    }
    /* detach right subtree and save in right-subtree */
    LinkedBinaryTree<T> rightSubtree;
    rightSubtree.root_ = root_->right_child_;
    count_ = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root_);
    root_->right_child_ = nullptr;
    tree_size_ -= rightSubtree.tree_size_;
    return rightSubtree;
}


template<typename T>
void LinkedBinaryTree<T>::preOrder(BinaryTreeNode<T> *tree) {
    if (tree != NULL) {
        LinkedBinaryTree<T>::visit(tree);
        preOrder(tree->left_child_);
        preOrder(tree->right_child_);
    }
}

template<typename T>
void LinkedBinaryTree<T>::inOrder(BinaryTreeNode<T> *tree) {
    if (tree != NULL) {
        inOrder(tree->left_child_);
        LinkedBinaryTree<T>::visit(tree);
        inOrder(tree->right_child_);
    }
}

template<typename T>
void LinkedBinaryTree<T>::postOrder(BinaryTreeNode<T> *tree) {
    if (tree != NULL) {
        postOrder(tree->left_child_);
        postOrder(tree->right_child_);
        LinkedBinaryTree<T>::visit(tree);
    }
}

template<typename T>
void LinkedBinaryTree<T>::levelOrder(void (*theVisit)(BinaryTreeNode<T> *)) {
    // level order traversal 
    ArrayQueue<BinaryTreeNode<T> *> arrayQueue;
    BinaryTreeNode<T> *tree = root_;
    while (root_ != nullptr) {
        theVisit(tree);

        if (tree->left_child_ != nullptr) {
            arrayQueue.push(tree->left_child_);
        }
        if (tree->right_child_ != nullptr) {
            arrayQueue.push(tree->right_child_);
        }
        // get next node to visit 
        try {
            tree = arrayQueue.front();
        }
        catch (QueueEmpty) {
            return;
        }
        arrayQueue.pop();
    }
}

template<typename T>
int LinkedBinaryTree<T>::height(BinaryTreeNode<T> *tree) {
    if (tree == nullptr) {
        return 0;
    }
    int hl = height(tree->left_child_);
    int hr = height(tree->right_child_);
    if (hl > hr) {
        return ++hl;
    } else {
        return ++hr;
    }
}

template<typename T>
vector<T> LinkedBinaryTree<T>::rightSideView(void (*theVisit)(BinaryTreeNode<T> *)) {
    // 声明一个队列
    ArrayQueue<BinaryTreeNode<T> *> queue;
    if (root_ != nullptr) {
        queue.push(root_);
    }
    vector<T> result;

    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            BinaryTreeNode<T> *node = queue.front();
            queue.pop();

            if (i == (size - 1)) {
                visit(node);
                result.push_back(node->element_);
            }
            if (node->left_child_) {
                queue.push(node->left_child_);
            }
            if (node->right_child_) {
                queue.push(node->right_child_);
            }
        }
    }
    return result;
}


#endif 
