//
// Created by CaoRui on 2021/6/6.
//

#ifndef DATASTRUCTURE_INDEXEDBSTREE_H
#define DATASTRUCTURE_INDEXEDBSTREE_H

#include "BsTree.h"

using namespace std;

template<typename K, typename E>
class IndexedBsTree : public BsTree<K, E> {
public:
    virtual pair<const K, E> *get(int) const = 0;

    virtual void deleter(int) = 0;
};

#endif //DATASTRUCTURE_INDEXEDBSTREE_H
