/*
 * =====================================================================================
 *
 *       Filename:  MyExceptions.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时23分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
// exception classes for various error types

#ifndef myExceptions_
#define myExceptions_

#include <exception>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

// illegal parameter value
class IllegalParameterValue : public std::exception {
public:
  explicit IllegalParameterValue(string theMessage = "Illegal parameter value") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// illegal input data
class IllegalInputData {
public:
  explicit IllegalInputData(string theMessage = "Illegal data input") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// illegal index
class IllegalIndex {
public:
  explicit IllegalIndex(string theMessage = "Illegal index") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// matrix index out of bounds
class MatrixIndexOutOfBounds {
public:
  explicit MatrixIndexOutOfBounds
      (string theMessage = "Matrix index out of bounds") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// matrix size mismatch
class MatrixSizeMismatch {
public:
  explicit MatrixSizeMismatch(string theMessage =
  "The size of the two matrices doesn't match") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// stack is empty
class StackEmpty {
public:
  explicit StackEmpty(string theMessage =
  "Invalid operation on empty stack") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// queue is empty
class QueueEmpty : public std::exception {
public:
  explicit QueueEmpty(string theMessage =
  "Invalid operation on empty queue") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// tree is empty
class TreeEmpty {
public:
  explicit TreeEmpty(string theMessage = "Invalid operation on empty tree") : message(std::move(theMessage)) {}

  void outputMessage() {
    cout << message << endl;
  }

private:
  string message;

};

// hash table is full
class HashTableFull {
public:
  explicit HashTableFull(string theMessage =
  "The hash table is full") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// edge weight undefined
class UndefinedEdgeWeight {
public:
  explicit UndefinedEdgeWeight(string theMessage =
  "No edge weights defined") { message = std::move(theMessage); }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

// method undefined
class UndefinedMethod {
public:
  explicit UndefinedMethod(string theMessage =
  "This method is undefined") { message = theMessage; }

  void outputMessage() { cout << message << endl; }

private:
  string message;
};

#endif

