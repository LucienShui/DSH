//
// Created by LucienShui on 2018/4/4.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <algorithm>
template <typename T>
struct Polynomial {
    T *coe; // coefficient
    int upper;
    Polynomial(int maxn = 1007) {
        upper = maxn;
        coe = new T[upper + 7];
        memset(coe, 0, sizeof(coe));
    }
    Polynomial(Polynomial &pol) {
        upper = pol.upper;
        coe = new T[upper + 7];
        memcpy(coe, pol, sizeof(coe));
    }
    Polynomial operator + (const Polynomial &tmp) const {
        Polynomial ret, a = *this, b = tmp;
        int l = a.upper, r = b.upper;
        if (l > r) std::swap(l, r);

    }
};

#endif //POLYNOMIAL_H

