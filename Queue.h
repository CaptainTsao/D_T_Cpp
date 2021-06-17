/*
 * =====================================================================================
 *
 *       Filename:  Queue.h
 *
 *    Description:  Abstract class queue 
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时41分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef Queue_H
#define Queue_H

using namespace std;

template<typename T>
class Queue {
public:
    virtual ~Queue() = default;
    /* return true iff queue is empty */
    virtual bool empty() const = 0;
    /* return number of elements in queue */
    virtual int size() const= 0;
    /* return reference to the front element */
    virtual T& front() = 0;
    /* return reference to the back element */
    virtual T& back() = 0;
    /* remove the front element */
    virtual void pop() = 0;
    /* add theElement at the back of of the queue */
    virtual void push(const T& theElement) = 0;
};

#endif
