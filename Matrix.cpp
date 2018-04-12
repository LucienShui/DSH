#include <bits/stdc++.h>
struct Matrix {
    std::map<std::pair<int, int>, int> data; // 初始时整个矩阵为0
    void insert(int x, int y, int val) { data[{x, y}] += val; } // 第x行第y列加上val
    Matrix operator ~ () { // 矩阵转置
        Matrix ret;
        for (auto it : data) ret.insert(it.first.second, it.first.first, it.second);
        return ret;
    }
    Matrix operator + (const Matrix &tmp) const { // 加法
        Matrix ret;
        for (auto it : (*this).data) ret.insert(it.first.first, it.first.second, it.second);
        for (auto it : tmp.data) ret.insert(it.first.first, it.first.second, it.second);
        return ret;
    }
    friend std::ostream & operator << (std::ostream &os, const Matrix &tmp)  { // 重载输出流
        for (auto it : tmp.data) if (it.second) // 如果当前元素的值不为零
            os << it.first.first << ' ' << it.first.second << ' ' << it.second << std::endl;
        return os;
    }
} a, b;
using namespace std;
int main() {
//    freopen("in.txt", "r", stdin);
    int n, x, y, val;
    for (scanf("%*d%*d%d", &n); n--; ) scanf("%d%d%d", &x, &y, &val), a.insert(x, y, val);
    for (scanf("%*d%*d%d", &n); n--; ) scanf("%d%d%d", &x, &y, &val), b.insert(x, y, val);
    cout << "The transformed matrix is:" << endl << ~a;
    cout << "The added matrix is:" << endl << a + b;
    return 0;
}

