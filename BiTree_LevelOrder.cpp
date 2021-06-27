//
// Created by rcao on 2021/6/27.
//

#include <iostream>
#include <memory>
#include <unordered_map>
#include <stack>
#include "Chain.h"
#include "LinkedBinaryTree.h"
#include "ArrayQueue.h"

template<typename T>
class Solution_LevelOrder {
private:
    ArrayQueue<BinaryTreeNode<T> *> array_queue{};
public:
    std::vector<std::vector<T>> LevelOrder_102(BinaryTreeNode<T> *root) {
        if (root != nullptr) {// if root is nullptr, root push into stack
            array_queue.push(root);
        }
        vector<vector<T>> result;
        while (!array_queue.empty()) {// traverse stack
            int size = array_queue.size();  // get stack size
            vector<T> vec;
//            for (BinaryTreeNode<T> *node : array_queue) {
//                array_queue.pop();
//                vec.push_back(node->element_);
//                if (node->left_child_) {
//                    array_queue.push(node->left_child_);
//                }
//                if (node->right_child_) {
//                    array_queue.push(node->right_child_);
//                }
//            }
            for (int i = 0; i < size; ++i) {
                BinaryTreeNode<T> *node = array_queue.front();  //
                array_queue.pop();
                vec.push_back(node->element_);
                if (node->left_child_)
                    array_queue.push(node->left_child_);
                if (node->right_child_)
                    array_queue.push(node->right_child_);
            }
            result.push_back(vec);
        }
        return result;
    }
};