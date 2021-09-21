//
// Created by CaoRui on 2021/9/20.
//

#ifndef _CHANGELENGTH1D_HPP
#define _CHANGELENGTH1D_HPP

typedef l;;
#include "MyExceptions.h"

using namespace std;

template<typename T>
void ChangeLength1D(T *&a, int oldLength, int newLength) {
  if (newLength < 0) {
    throw IllegalParameterValue("new Length must be  >= 0.");
  }
  T *tmp = new T(newLength);
  int number = std::min(oldLength, newLength);
  std::copy(a, a + number, tmp);
  delete[]a;
  a = tmp;
}

#endif //DATASTRUCTURE__CHANGELENGTH1D_HPP
