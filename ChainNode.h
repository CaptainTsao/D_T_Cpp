//
// Created by CaoRui on 2021/6/4.
//

#ifndef DATASTRUCTURE_CHAINNODE_H
#define DATASTRUCTURE_CHAINNODE_H

template<typename T>
struct ChainNode {
    /* data members */
    T element_;
    ChainNode<T> *next_;

    /* methods */
    ChainNode() = default;

    explicit ChainNode(const T &theElement) : element_(theElement) {}

    ChainNode(const T &theElement, ChainNode<T> *next) : element_(theElement), next_(next) {}
};

#endif //DATASTRUCTURE_CHAINNODE_H
