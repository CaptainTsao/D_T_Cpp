//
// Created by CaoRui on 2021/6/5.
//

#include <iostream>
#include "BinaryTreeNode.h"

using namespace std;

template<typename T>
void Infix(BinaryTreeNode<T> *tree) {
    /* Output infix form of expression */
    if (tree != nullptr) {
        cout << '(';
        Infix(tree->left_child_);   // left operand
        cout << tree->element_;     // operator
        Infix(tree->right_child_);  // right operand
        cout << ')';
    }
}

int main() {
    BinaryTreeNode<int> x, y, z;
    x.element_ = 1;
    y.element_ = 2;
    z.element_ = 3;
    x.left_child_ = &y;
    x.right_child_ = &z;
    y.left_child_ = y.right_child_ = z.left_child_ = z.right_child_ = 0;
    Infix(&x);
    cout << endl;

    return 0;
}