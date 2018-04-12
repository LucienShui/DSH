//
// Created by LucienShui on 2018/4/4.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cstring>
#include <iostream>
#include <algorithm>

struct Polynomial {
    struct Node {
        int coe, index;
        Node *next;
        Node(int coe = -1, int index= -1, Node *next = nullptr):coe(coe), index(index), next(next) {}
        void clear() { // 递归删除整个链表
            if (next) next->clear();
            delete this;
        }
    } *head = nullptr; // coefficient
    int size = 0;

    Polynomial() { head = new Node; }

    ~Polynomial() { head->clear(); }

    void insert(int coe, int index) { // 如果能找到同次方的就将系数加和，否则新建一个节点
        if (!head) head = new Node;
        Node *cur = head;
        while (cur->next && cur->next->index < index) cur = cur->next; // 找到第一个系数大于等于index的节点的前一个节点
        if (cur->next) {
            if (cur->next->index == index) cur->next->coe += coe; // 如果键值相等
            else {
                Node *tmp = cur->next;
                cur->next = new Node(coe, index, tmp);
                size++;
            }
        } else cur->next = new Node{coe, index}, size++; // 如果已经到了末尾
    }

    Polynomial(Polynomial &tmp) { // 拷贝函数直接暴力n^2插入，毕竟作业，忽略复杂度
        for (Node *cur = tmp.head->next; cur; cur = cur->next) insert(cur->coe, cur->index);
    }

    Polynomial operator + (Polynomial &tmp) { // 多项式加法，利用insert函数的性质，直接n^2暴力插入就可实现功能
        Polynomial ret = *this;
        for (Node *cur = tmp.head->next; cur; cur = cur->next) ret.insert(cur->coe, cur->index);
        return ret;
    }

    Polynomial operator ~ () const { // 求导
        Polynomial ret;
        for (Node *cur = head->next; cur; cur = cur->next) if (cur->index) ret.insert((cur->coe) * (cur->index), cur->index - 1);
        return ret;
    }

    friend std::ostream & operator << (std::ostream &os, const Polynomial &tmp) { // 重载输出流
        if (tmp.size < 1) os << 0;
        else {
            Node *cur = tmp.head->next;
            bool flag = false;
            for (int coe, index; cur; cur = cur->next) {
                if (!(coe = cur->coe)) continue;
                index = cur->index;
                if (flag && coe > 0) os << '+';
                flag = true;
                if (abs(coe) == 1) {
                    if (coe < 0) os << '-';
                } else os << coe;
                if (index) os << 'x';
                if (index > 1) os << '^' << index;
            }
        }
        return os;
    }

    long long qpow(int p, int q) { // 快速幂
        long long ret = 1;
        while (q) {
            if (q & 1) ret *= p;
            p *= p, q >>= 1;
        }
        return ret;
    }

    long long calculate(int num) { // 计算f(x)
        long long ret = 0;
        for (Node *cur = head->next; cur; cur = cur->next) ret += cur->coe * qpow(num, cur->index);
        return ret;
    }
};

#endif //POLYNOMIAL_H
