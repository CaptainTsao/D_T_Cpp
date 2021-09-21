//
// Created by CaoRui on 2021/9/20.
//

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <sstream>
#include "Queue.h"
#include "ChainNode.h"
#include "MyExceptions.h"

using namespace std;

template<typename T>
class LinkedQueue : public Queue<T> {
public:
  explicit LinkedQueue(int initial_capacity = 10);

  bool empty() const override {
    return queue_size_ == 0;
  }

  int size() const override {
    return queue_size_;
  }

  T &front() override {
    if (0 == queue_size_) {
      throw QueueEmpty();
    }
    return queue_front_->element_;
  }

  T &back() override {
    if (0 == queue_size_) {
      throw QueueEmpty();
    }
    return queue_back_->element_;
  }

  void pop_front() override;

  void push_back(const T &) override;

  ~LinkedQueue() override;
private:
  ChainNode<T> *queue_front_;     /* pointer to queue front */
  ChainNode<T> *queue_back_;      /* pointer to queue end */
  int queue_size_;                /* number of elements in the queue */
};

template<typename T>
LinkedQueue<T>::LinkedQueue(int initial_capacity)
    :queue_front_(nullptr), queue_back_(nullptr), queue_size_(initial_capacity) {}
template<typename T>
void LinkedQueue<T>::pop_front() {
  if (queue_front_ == nullptr) {
    throw QueueEmpty();
  }

  ChainNode<T> *next_node = queue_front_->next_;
  delete queue_front_;
  queue_front_ = next_node;
  queue_size_--;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
  /* Destructor */
  while (queue_front_ != nullptr) {
    /* delete front node */
    ChainNode<T> *next_node = queue_front_->next_;
    delete queue_front_;
    queue_front_ = next_node;
  }
}

template<typename T>
void LinkedQueue<T>::push_back(const T &the_element) {
  /* Add element into the back of queue. */
  /* create node for new element */
  auto *new_node = new ChainNode<T>(the_element, nullptr);

  /* add new node to the back of queue */
  if (0 == queue_size_) {
    queue_front_ = new_node;        /* queue empty */
  } else {
    queue_back_->next_ = new_node;  /* queue not empty */
  }
  queue_back_ = new_node;
  queue_size_++;
}

#endif //LINKEDQUEUE_H
