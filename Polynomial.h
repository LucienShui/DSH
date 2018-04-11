//
// Created by LucienShui on 2018/4/4.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cstring>
#include <iostream>
#include <algorithm>

struct Polynomial {
    int *data; // coefficient
    int maxsize, upper;

    explicit Polynomial(int maxn = 1007) {
        maxsize = maxn, upper = -1;
        data = new int[maxsize + 7];
        memset(data, 0, sizeof(data));
    }

    Polynomial(Polynomial &pol) {
        upper = pol.upper;
        maxsize = pol.maxsize;
        data = new int[maxsize + 7];
        memcpy(data, pol.data, sizeof(pol.data));
    }

    void update(int coe, int index) {
        data[index] = coe;
        upper = std::max(index, upper);
    }

    Polynomial operator + (Polynomial &tmp) { // 多项式加法
        Polynomial ret(std::max(tmp.maxsize, maxsize));
        ret.upper = std::max(tmp.upper, upper);
        for (int i = 0; i <= ret.upper; i++) ret.data[i] = data[i] + tmp.data[i];
        return ret;
    }

    Polynomial operator ~ () const { // 求导
        Polynomial ret(maxsize);
        ret.upper = upper - 1;
        for (int i = 1; i <= upper; i++) ret.data[i - 1] = data[i] * i;
        return ret;
    }

    friend std::ostream & operator << (std::ostream &os, const Polynomial &tmp) {
        if (tmp.upper < 1) os << tmp.upper ? 0 : tmp.data[0];
        else {
            int cur = 0;
            while (tmp.data[cur] == 0 && cur <= tmp.upper) cur++;
            if (cur > tmp.upper) os << 0;
            else {
                bool flag = false;
                for (int coe; cur <= tmp.upper; cur++)
                    if (tmp.data[cur]) {
                        coe = tmp.data[cur];
                        if (flag && coe > 0) os << '+';
                        flag = true;
                        if (abs(coe) == 1) {
                            if (coe < 0) os << '-';
                        } else os << coe;
                        if (cur) os << 'x';
                        if (cur > 1) os << '^' << cur;
                    }
            }
        }
        return os;
    }

    long long calculate(int num) {
        long long ret = 0, base = 1;
        for (int i = 0; i <= upper; i++, base *= num) ret += data[i] * base;
        return ret;
    }
} a, b;

#endif //POLYNOMIAL_H

using namespace std;
int main() {
//    freopen("in.txt", "r", stdin);
    int n, coe, num;
    for (cin >> n; n--; ) cin >> coe >> num, a.update(coe, num);
    for (cin >> n; n--; ) cin >> coe >> num, b.update(coe, num);
    cout << "A(x)+B(x)=" << a + b << endl;
    cout << "A'(x)=" << ~a << endl;
    cin >> num;
    cout << "A(" << num << ")=" << a.calculate(num) << endl;
    return 0;
}
