//
// Created by CaoRui on 2021/6/6.
//

#ifndef DATASTRUCTURE_DBINARYSEARCHTREE_H
#define DATASTRUCTURE_DBINARYSEARCHTREE_H

#include "BinarySearchTree.h"

using namespace std;

template<typename K, typename E>
class dBinarySearchTree : public BinarySearchTree<K, E> {
public:
    /* override insert method of BinarySearchTree */
    void insert(const pair<const K, E> &) override;
};

template<typename K, typename E>
void dBinarySearchTree<K, E>::insert(const pair<const K, E> &thePair) {

}

#endif //DATASTRUCTURE_DBINARYSEARCHTREE_H
