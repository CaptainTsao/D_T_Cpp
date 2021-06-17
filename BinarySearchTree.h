//
// Created by CaoRui on 2021/6/6.
//

#ifndef DATASTRUCTURE_BINARYSEARCHTREE_H
#define DATASTRUCTURE_BINARYSEARCHTREE_H

#include "BsTree.h"
#include "LinkedBinaryTree.h"

using namespace std;

template<typename K, typename E>
class BinarySearchTree : public BsTree<K, E>, public LinkedBinaryTree<pair<const K, E>> {
public:
    /* methods of dictionary */
    bool empty() const override {
        return 0 == this->tree_size_;
    }

    int size() const override {
        return this->tree_size_;
    }

    pair<const K, E> *find(const K &theKey) const override;

    void insert(const pair<const K, E> &thePair);

    void erase(const K &theKey);

    // additional method of bsTree
//    void ascend() {
//        InOrderPut();
//    }
};

template<class K, class E>
pair<const K, E> *BinarySearchTree<K, E>::find(const K &theKey) const {
    /* return pointer to matching pair */
    /* return nullptr if no matching pair */

    BinaryTreeNode<pair<const K, E>> *p = this->root_;
    while (p != nullptr) {
        /* examine p->element_ */
        if (theKey < p->element_.first) {
            p = p->left_child_;
        } else {
            if (theKey > p->element_.first) {
                p = p->right_child_;
            } else {     /* founding matching pair */
                return &p->element_;
            }
        }
    }
    /* no matching pair */
    return nullptr;
}

template<class K, class E>
void BinarySearchTree<K, E>::insert(const pair<const K, E> &thePair) {
    /* Insert thePair into the tree. Overwrite existing
     * pair, if nay, with same key.
     * find place to insert. */
    BinaryTreeNode<pair<const K, E>> *p = this->root_, *pp = nullptr;
    while (p != nullptr) {
        /* examine p->element_ */
        pp = p;
        /* move p to a child */
        if (thePair.first < p->element_.first) {
            p = p->right_child_;
        } else {
            if (thePair.first > p->element_.first) {
                p = p->right_child_;
            } else { // replace old value
                p->element_.second = thePair.second;
            }
        }
    }
    /* get a node for thePair and attach to pp */
    auto *newNode = new BinaryTreeNode<pair<const K, E>>(thePair);
    if (this->root_ != nullptr) { /* the tree is not empty */
        if (thePair.first < pp->element_.first) {
            pp->left_child_ = newNode;
        } else {
            pp->right_child_ = newNode;
        }
    } else {
        this->root_ = newNode;
    }
    this->tree_size_++;
}

template<class K, class E>
void BinarySearchTree<K, E>::erase(const K &theKey) {
    /* Delete the pair, if any, whose key equals theKey */
    BinaryTreeNode<pair<const K, E>> *p = this->root_, *pp = nullptr;

    while (p != nullptr && p->element_.first != theKey) {
        /* move to a child of p */
        pp = p;
        if (theKey < p->element_.first) {
            p = p->left_child_;
        } else {
            p = p->right_child_;
        }
    }
    if (p == nullptr) {
        return;
    }
    /* restructure tree
     * handle case when p has two children */
    if (p->left_child_ != nullptr && p->right_child_ != nullptr) {
        /* two children
         * convert to zero or one child case
         * find largest element in the left subtree of p */
        BinaryTreeNode<pair<const K, E>> *s = p->left_child_, *ps = p;// parent of s

        while (s->right_child_ != nullptr) {
            // move to larger element
            ps = s;

            s = s->right_child_;
        }
        /* move largest from s to p, can't do a simple move
         * p->element_ = s->element_ as key is const */
        BinaryTreeNode<pair<const K, E>> *q =
          new BinaryTreeNode<pair<const K, E>>(s->element_, p->left_child_, p->right_child_);
        if (pp == nullptr) {
            this->root_ = q;
        } else {
            if (p == pp->left_child_) {
                pp->left_child_ = q;
            } else {
                pp->right_child_ = q;
            }
        }

        if (ps == p) {
            pp = q;
        } else {
            pp = ps;
        }
        delete p;
        p = s;
    }
    /* p has at most one child
     * save child pointer in c */
    BinaryTreeNode<pair<const K, E>> *c;
    if (p->left_child_ != nullptr) {
        c = p->left_child_;
    } else {
        c = p->right_child_;
    }
    /* if delete p */
    if (p == this->root_) {
        this->root_ = c;
    } else {    /* is p left or right child of pp? */
        if (p == pp->left_child_) {
            pp->left_child_ = c;
        } else {
            pp->right_child_ = c;
        }
    }
    this->tree_size_--;
    delete p;
}


/* overload << for pair */
template<typename K, typename E>
ostream &operator<<(ostream &out, const pair<K, E> &x) {
    out << x.first << ' ' << x.second;
    return out;
}

#endif //DATASTRUCTURE_BINARYSEARCHTREE_H
