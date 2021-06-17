//
// Created by CaoRui on 2021/6/5.
//

#ifndef DATASTRUCTURE_DICTIONARY_H
#define DATASTRUCTURE_DICTIONARY_H

#include <bitset>

using namespace std;

template<typename K, typename E>
class Dictionary {
public:
    virtual ~Dictionary() = default;

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual pair<const K, E> *find(const K &) const = 0;

    virtual void erase(const K &) = 0;

    virtual void insert(const pair<const K, E> &) = 0;
};

#endif //DATASTRUCTURE_DICTIONARY_H
