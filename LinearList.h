//
// Created by CaoRui on 2021/6/4.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

#include <iostream>

using namespace std;

template<typename T>
class LinearList {
public:
    virtual ~LinearList() = default;

    /* return true iff list is empty */
    virtual bool empty() const = 0;

    /* return number of elements in list */
    virtual size_t size() const = 0;

    /* return element whose index is theIndex */
    virtual T &get(int theIndex) const = 0;

    /* return index of first occurrence of the theElement */
    virtual int indexOf(const T &theElement) const = 0;

    /* remove the element whose index is theIndex */
    virtual void erase(int theIndex) = 0;

    /* insert theElement so that its index is theIndex */
    virtual void insert(int theIndex, const T &theElement) = 0;

    /* insert list into stream out */
    virtual void output(ostream &out) const = 0;
};

#endif //DATASTRUCTURE_LINEARLIST_H
