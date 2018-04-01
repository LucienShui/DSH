//
// Created by LucienShui on 2018/3/30.
//

#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <iostream>
#include <algorithm>
template <typename T>
class List {
private:
    struct Node {
        Node *pre, *next;
        T val;
        Node(Node *pre = nullptr, Node *next = nullptr, T val = T(0)):pre(pre), next(next), val(val) {}
        void Clear() {
            if (next) next->Clear();
            delete next;
            next = nullptr;
        }
    } *head, *tail;
    int length;
public:
    List() {
        length = 0, tail = new Node(head = new Node()), head->next = tail;
    }
    List(const List &list) {
        length = list.length, tail = new Node(head = new Node());
        Node *cur = head, *pre = head;
        for (Node *i = list.head->next; i->next; i = i->next) {
            Node *&tmp = cur->next;
            tmp = new Node(pre, nullptr, i->val), pre = cur, cur = cur->next;
        }
        tail->pre = cur, cur->next = tail;
    }
    ~List() {
        head->Clear();
    }
    bool insert(T val, int index = -1) {
        if (index > length) return false;
        Node *cur = nullptr, *tmp = nullptr;
        if (~index) {
            cur = head->next;
            for (int cnt = 0; cnt < index && cur->next; cur = cur->next, cnt++);
        } else cur = tail->pre->next;
        tmp = cur->pre;
        cur->pre = tmp->next = new Node(tmp, cur, val);
        length++;
        return true;
    }
    bool remove(T val) {
        Node *cur = head->next;
        while (cur->val != val && cur->next) cur = cur->next;
        if (cur->val != val) return false;
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;
        delete cur;
        length--;
        return true;
    }
    int size() { return length; }
    T operator [] (int index) {
        if (index >= length || index < 0) exit(1);
        int cnt = 0;
        Node *cur = head->next;
        while (cur->next && cnt++ < index) cur = cur->next;
        return cur->val;
    }
    friend std::ostream & operator << (std::ostream &os, const List &tmp) {
        Node *cur = tmp.head->next;
        while (cur->next->next) os << cur->val << ' ', cur = cur->next;
        os << cur->val;
        return os;
    }
    List operator | (const List &list) const {
        List ret = *this;
        int cnt = 0;
        T tmp[this->length + 7];
        for (Node *cur = this->head->next; cur->next; cur = cur->next) tmp[cnt++] = cur->val;
        std::sort(tmp, tmp + cnt);
        for (Node *i = list.head->next; i->next; i = i->next) {
            int cur = int(std::lower_bound(tmp, tmp + cnt, i->val) - tmp);
            if (cur >= cnt || tmp[cur] != i->val) ret.insert(i->val);
        }
        return ret;
    }
    List operator & (List const &list) const {
        List ret;
        for (Node *a = list.head->next; a->next; a = a->next)
            for (Node *b = this->head->next; b->next; b = b->next)
                if (b->val == a->val) {
                    ret.insert(a->val);
                    break;
                }
        return ret;
    }
    List sort() {
        List ret;
        T tmp[this->length + 7];
        int cnt = 0;
        for (Node *cur = this->head->next; cur->next; cur = cur->next) tmp[cnt++] = cur->val;
        std::sort(tmp, tmp + this->length);
        for (int i = 0; i < cnt; i++) ret.insert(tmp[i]);
        return ret;
    }
    int index(T val) {
        int index = 0;
        for (Node *cur = head->next; cur->next; cur = cur->next, index++) if (cur->val == val) return index;
        return -1;
    }
};

#endif //TEST_LIST_H
