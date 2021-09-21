//
// Created by CaoRui on 2021/9/20.
//

#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "maxPriorityQueue.hpp"
#include "MyExceptions.h"
#include "changeLength1D.hpp"

#include <sstream>
#include <algorithm>

using namespace std;

template<typename T>
class MaxHeap : public MaxPriorityQueue<T> {
public:
  explicit MaxHeap(int initial_capacity = 10);

  bool empty() const {
    return 0 == heapSize;
  }

  int size() const {
    return heapSize;
  }

  const T &top() {
    if (0 == heapSize) {
      throw QueueEmpty();
    }
    return heap[1];
  }

  void pop();

  void push(const T &);

  void initialize(T *, int);

  void deactivateArray() {
    heap = nullptr;
    arrayLength = heapSize = 0;
  }

  void output(ostream &out) const;

  ~MaxHeap() {
    delete[] heap;
  }
private:
  int heap_size_;       /* number of elements in queue */
  int array_length_;    /* queue capacity + 1*/
  T *heap_;            /* element array */
};

template<typename T>
MaxHeap<T>::MaxHeap(int initial_capacity)
    : heap_size_(0), array_length_(initial_capacity + 1), heap_(new T[array_length_]) {
  if (initial_capacity < 1) {
    s << "Initial Capacity = " << initial_capacity << " Must be  > 0. ";
    throw IllegalParameterValue(s.str());
  }
}

template<typename T>
void MaxHeap<T>::push(const T &the_element) {
  /* Add element into heap */
  // increase array length if necessary
  if (heap_size_ == array_length_ - 1) {
    ChangeLength1D(heap_, array_length_, 2 * array_length_);
    array_length_ *= 2;
  }
  /* find place for theElement
   * currentNode starts at new leaf and moves up tree */
  int current_node = ++heap_size_;
  while (current_node != 1 && heap[current_node / 2] < the_element) {
    /* cannot put theElement in heap[currentNode] */
    heap_[current_node] = heap_[current_node / 2];    /* move element down */
    current_node /= 2;                                /* move to parent */
  }
  heap_[current_node] = the_element;
}
template<typename T>
void MaxHeap<T>::pop() {
  /* remove max element */
  if (0 == heap_size_) {
    throw QueueEmpty();
  }

  /* 删除最大值元素 */
  heap_[1].~T();
  /* 删除最后一个元素，然后重新建堆 */
  T last_element = heap_[heap_size_--];
  /* find place for last element starting at root */
  int current_node = 1, child = 2;
  while (child <= heap_size_) {
    /* heap_[child] should be larger child of current_node */
    if (child < heap_size_ && heap_[child] < heap_[child + 1])
      child++;
    /* can we put last_element in heap_[current_node] */
    if (last_element >= heap_[child]) {
      break;
    }
    /* no */
    heap_[current_node] = heap_[child];
    current_node = child;
    child *= 2;
  }
  heap_[current_node] = last_element;
}
template<typename T>
void MaxHeap<T>::initialize(T *the_heap, int the_size) {
  delete[]heap_;
  heap_ = the_heap;
  heap_size_ = the_size;

  /* heapify */
  for (int root = heap_size_ / 2; root >= 1; --root) {
    T root_element = heap_[root];

    /* find place to put root_element */
    int child = 2 * root;

    while (child <= heap_size_) {
      /* heap_[child] should be larger sibling */
      if (child < heap_size_ && heap_[child] < heap_[child + 1])
        child++;

      /* can we put root_element in heap[child/2]? */
      if (root_element >= heap_[child])
        break;/*yes*/
      /* no */
      heap_[child / 2] = heap_[child];
      child *= 2;
    }
    heap_[child / 2] = root_element;
  }
}
template<typename T>
void MaxHeap<T>::output(ostream &out) const {
  copy(heap_ + 1, heap_ + heap_size_ = 1, ostreambuf_iterator<T>(cout, " "));
}

template<typename T>
ostream &operator<<(ostream &out, const MaxHeap<T> &x) {
  x.output(out);
  return out;
}
#endif //MAX_HEAP_HPP
