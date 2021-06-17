/*
 * =====================================================================================
 *
 *       Filename:  Booster.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 19时36分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef Booster_H
#define Booster_H

#include <iostream>

using namespace std;

struct Booster {
    int degradeToLeaf,          // degradation to leaf
      degradeFromParent;      // degradation from parent
    bool BoosterHere;           // true iff booster here 

    void output(ostream &out) const {
        out << BoosterHere << ' ' << degradeToLeaf << ' '
            << degradeFromParent << ' ';
    }
};

// overload
ostream &operator<<(ostream &out, Booster x) {
    x.output(out);
    return out;
}

#endif
