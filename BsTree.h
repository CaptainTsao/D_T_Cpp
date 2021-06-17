//
// Created by CaoRui on 2021/6/5.
//
// Abstract class BsTree
// Abstract data type specification for binary search trees
// all methods are pure virtual functions
// K is key type and E is value type


#ifndef DATASTRUCTURE_BSTREE_H
#define DATASTRUCTURE_BSTREE_H

#include "Dictionary.h"

using namespace std;

template<typename K, typename E>
class BsTree : public Dictionary<K, E> {
public:
    virtual void ascend() = 0;
};

#endif //DATASTRUCTURE_BSTREE_H
