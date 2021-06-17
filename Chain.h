//
// Created by CaoRui on 2021/6/4.
//

#ifndef DATASTRUCTURE_CHAIN_H
#define DATASTRUCTURE_CHAIN_H

#include <iostream>
#include <sstream>
#include <string>
#include "LinearList.h"
#include "ChainNode.h"
#include "MyExceptions.h"

using namespace std;

class LinkedDigraph;

template<typename T>
class LinkedWDigraph;

template <typename T>
class Solution;

template<typename T>
class Chain : public LinearList<T> {
    friend LinkedDigraph;
    friend LinkedWDigraph<int>;
    friend LinkedWDigraph<float>;
    friend LinkedWDigraph<double>;

public:
    friend Solution<T>;
public:
    /* constructor, copy constructor and destructor */
    explicit Chain(int initialCapacity = 10);

    Chain(const Chain<T> &);

    ~Chain();

    /* ADT methods */
    bool empty() const override {
        return 0 == lise_size_;
    }

    size_t size() const override {
        return lise_size_;
    }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(ostream &out) const;

    /* iteration to start and end of list */
    class iterator;

    iterator begin() {
        return iterator(first_node_);
    }

    iterator end() {
        return iterator(nullptr);
    }

    /* iteration for chain */
    class iterator {
    public:
        /* typedefs required by C++ for a forward iterator */
        typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        /* constructor */
        explicit iterator(ChainNode<T> *theNode = nullptr) {
            node_ = theNode;
        }

        /* deference operators */
        T &operator*() const {
            return node_->element_;
        }

        T *operator->() const {
            return &node_->element_;
        }

        /* increment */
        iterator &operator++() {    // pre-increment
            node_ = node_->next_;
            return *this;
        }

        iterator operator++(int) {  // post-increment
            iterator old = *this;
            node_ = node_->next_;
            return old;
        }

        /* equality testing */
        bool operator!=(const iterator rhs) const {
            return this->node_ != rhs.node_;
        }

        bool operator==(const iterator rhs) const {
            return this->node_ == rhs.node_;
        }

    protected:
        ChainNode<T> *node_;
    };

protected:
    void checkIndex(int theIndex) const;

    ChainNode<T> *first_node_;      /* pointer to first node in chain */
    int lise_size_;                 /* number of elements in list */
};

template<typename T>
Chain<T>::Chain(int initialCapacity) {
    /* Constructor */
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameterValue(s.str());
    }
    first_node_ = nullptr;
    lise_size_ = 0;
}

template<typename T>
Chain<T>::Chain(const Chain<T> &theList) {
    /* Copy Constructor */
    lise_size_ = theList.lise_size_;

    if (0 == lise_size_) {
        first_node_ = nullptr;
        return;
    }
    /* non-empty list */
    ChainNode<T> *sourceNode = theList.first_node_;    /* node in theList to copy from */
    first_node_ = new ChainNode<T>(sourceNode->element_);
    sourceNode = sourceNode->next_;
    /* current last node in *this */
    ChainNode<T> *targetNode = first_node_;
    while (sourceNode != nullptr) {
        /* copy remaining elements */
        targetNode->next_ = new ChainNode<T>(sourceNode->element_);
        targetNode = targetNode->next_;
        sourceNode = sourceNode->next_;
    }
    targetNode->next_ = nullptr;
}

template<typename T>
Chain<T>::~Chain() {
    /* Chain destructor. Delete all nodes in chain */
    while (first_node_ != nullptr) {
        /* Delete first_node_ */
        ChainNode<T> *nextNode = first_node_->next_;
        delete first_node_;
        first_node_ = nextNode;
    }
}

template<typename T>
void Chain<T>::checkIndex(int theIndex) const {
    /* Verify that theIndex is between 0 and list_size_-1 */
    if (theIndex < 0 || theIndex >= lise_size_) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << lise_size_;
        throw IllegalIndex(s.str());
    }
}

template<typename T>
T &Chain<T>::get(int theIndex) const {
    /* return element whose index is theIndex */
    /* Throw i*/
    checkIndex(theIndex);
    /* mode to desired node */
    ChainNode<T> *currentNode = first_node_;
    for (int i = 0; i < theIndex; ++i) {
        currentNode = currentNode->next_;
    }
    return currentNode->element_;
}

template<typename T>
int Chain<T>::indexOf(const T &theElement) const {
    /* return index of first occurrence of theElement*/
    // search the chain for theElement
    ChainNode<T> *currentNode = first_node_;
    int index = 0;// index of currentNode
    while (currentNode != nullptr && currentNode->element_ != theElement) {
        currentNode = currentNode->next_;
        index++;
    }
    // make sure we found matching element
    if (currentNode != nullptr) {
        return -1;
    } else {
        return index;
    }
}

template<typename T>
void Chain<T>::erase(int theIndex) {
    /* Delete the element whose index is theIndex */
    checkIndex(theIndex);

    /* valid index, locate node with element to delete */
    ChainNode<T> *deleteNode;
    if (0 == theIndex) {
        deleteNode = first_node_;
        first_node_ = first_node_->next_;
    } else {
        ChainNode<T> *p = first_node_;
        for (int i = 0; i < theIndex - 1; ++i) {
            p = p->next_;
        }
        deleteNode = p->next_;
        p->next_ = p->next_->next_;
    }
    lise_size_--;
    delete deleteNode;
}

template<typename T>
void Chain<T>::insert(int theIndex, const T &theElement) {
    /* Insert theElement so that its index is theIndex */
    if (theIndex < 0 || theIndex > lise_size_) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << lise_size_;
        throw IllegalIndex(s.str());
    }

    if (0 == theIndex) {
        first_node_ = new ChainNode<T>(theElement, first_node_);
    } else {
        /* find preprocessor of new element */
        ChainNode<T> *p = first_node_;
        for (int i = 0; i < theIndex - 1; ++i) {
            p = p->next_;
        }
        p->next_ = new ChainNode<T>(theElement, p->next_);
    }
    lise_size_++;
}

template<typename T>
void Chain<T>::output(ostream &out) const {
    /* put the list into the stream out */
    for (ChainNode<T> *currentNode = first_node_;
         currentNode != nullptr;
         currentNode = currentNode->next_) {
        out << currentNode->element_ << " ";
    }
}

/* overload << */
template<typename T>
ostream &operator<<(ostream &out, const Chain<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_CHAIN_H
