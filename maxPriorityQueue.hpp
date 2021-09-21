//
// Created by CaoRui on 2021/9/20.
//

#ifndef MAX_PRIORITY_QUEUE_HPP
#define MAX_PRIORITY_QUEUE_HPP

using namespace std;

template<typename T>
class MaxPriorityQueue {
public:
  virtual ~MaxPriorityQueue() = default;
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual const T &top() = 0;
  /* remove the top element */
  virtual void pop() = 0;
  /* add the element into the queue */
  virtual void push(const T &the_element) = 0;
};

#endif //MAX_PRIORITY_QUEUE_HPP
