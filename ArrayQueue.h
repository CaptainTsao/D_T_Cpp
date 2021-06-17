/*
 * =====================================================================================
 *
 *       Filename:  ArrayQueue.h
 *
 *    Description:  circular array implementation of a queue derives from the ADT queue 
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时43分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ArrayQueue_H
#define ArrayQueue_H

#include "Queue.h"
#include "MyExceptions.h"
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class ArrayQueue : public Queue<T> {
public:
    explicit ArrayQueue(int initialCapacity = 10);

    ~ArrayQueue() override { delete[] queue_; }

    bool empty() const override {
        return the_front_ == the_back_;
    }

    int size() const override {
        return (the_back_ - the_front_ + array_length_) % array_length_;
    }

    T &front() override {
        if (the_front_ == the_back_) {
            throw QueueEmpty();
        }
        return queue_[(the_front_ + 1) % array_length_];
    }

    T &back() override {
        if (the_front_ == the_back_) {
            throw QueueEmpty();
        }
        return queue_[the_back_];
    }

    void pop() override {
        if (the_front_ == the_back_) {
            throw QueueEmpty();
        }
        the_front_ = (the_front_ + 1) % array_length_;
        queue_[the_front_].~T();
    }

    void push(const T &theElement) override;

private:
    int the_front_;
    int the_back_;
    int array_length_;
    T *queue_;       // element array
};


template<typename T>
ArrayQueue<T>::ArrayQueue(int initialCapacity) {
    // constructor
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << " Must be > 0";
        throw IllegalParameterValue(s.str());
    }
    array_length_ = initialCapacity;
    queue_ = new T[initialCapacity];
    the_front_ = 0;
    the_back_ = 0;
}

template<typename T>
void ArrayQueue<T>::push(const T &theElement) {
    // add theElement into queue 
    if ((the_back_ + 1) % array_length_ == the_front_) {
        T *newQueue = new T[2 * array_length_];
        // copy elements into newQueue 
        int start = (the_front_ + 1) % array_length_;
        if (start < 2) {
            copy(queue_ + start, queue_ + start + array_length_ - 1, newQueue);
        } else {
            copy(queue_ + start, queue_ + array_length_, newQueue);
            copy(queue_, queue_ + the_back_ + 1, newQueue + array_length_ - start);
        }
        //
        the_front_ = 2 * array_length_ - 1;
        the_back_ = array_length_ - 2;
        array_length_ *= 2;
        queue_ = newQueue;
    }
    // put theElement at the theBack of queue
    the_back_ = (the_back_ + 1) % array_length_;
    queue_[the_back_] = theElement;
}


#endif

