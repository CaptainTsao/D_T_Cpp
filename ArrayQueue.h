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
  explicit ArrayQueue(int initial_capacity = 10);

  ~ArrayQueue() {
    delete[] queue_;
  }

  bool empty() const {
    return the_front_ == the_back_;
  }

  int size() const {
    return (the_back_ - the_front_ + array_length_) % array_length_;
  }

  T &front() {
    if (the_front_ == the_back_) {
      throw QueueEmpty();
    }
    return queue_[(the_front_ + 1) % array_length_];
  }

  T &back() {
    if (the_front_ == the_back_) {
      throw QueueEmpty();
    }
    return queue_[the_back_];
  }

  void pop_front() override {
    if (the_front_ == the_back_) {
      throw QueueEmpty();
    }
    the_front_ = (the_front_ + 1) % array_length_;
    queue_[the_front_].~T();
  }

  void push_pack(const T &the_element);

private:
  int the_front_;       /* index to front element */
  int the_back_;        /* index to end element */
  int array_length_;    /* length of queue */
  T *queue_;            // element array
};

template<typename T>
ArrayQueue<T>::ArrayQueue(int initial_capacity)
    :the_front_(0), the_back_(0), array_length_(initial_capacity), queue_(new T[initial_capacity]) {
  // constructor
  if (initial_capacity < 1) {
    ostringstream s;
    s << "Initial Capacity = " << initial_capacity << " Must be > 0";
    throw IllegalParameterValue(s.str());
  }
}

template<typename T>
void ArrayQueue<T>::push_pack(const T &the_element) {
  // Add theElement into queue
  if ((the_back_ + 1) % array_length_ == the_front_) {
    T *new_queue = new T[2 * array_length_];
    // copy elements into newQueue
//    int start = (the_front_ + 1) % array_length_;
    int start = the_front_ % array_length_;
    if (start < 2) {
      /* no wrap around */
      copy(queue_ + start, queue_ + start + array_length_ - 1, new_queue);
    } else {
      /* queue wraps around */
      copy(queue_ + start, queue_ + array_length_, new_queue);
      copy(queue_, queue_ + the_back_ + 1, new_queue + array_length_ - start);
    }
    // switch to new_queue and set `the_front_` and `the_back_`
    the_front_ = 2 * array_length_ - 1;
    the_back_ = array_length_ - 2;
    array_length_ *= 2;
    queue_ = new_queue;
  }

  // put the_element at the the_back_ of queue
  the_back_ = (the_back_ + 1) % array_length_;
  queue_[the_back_] = the_element;
}

#endif

