#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <iostream>
#include <algorithm>
template <typename T>
class List { // 双链表
private:
    struct Node { // 链表节点
        Node *pre, *next; // 分别指向上一个节点和下一个节点
        T val; // 当前节点的键值，需要重载小于号
        Node(Node *pre = nullptr, Node *next = nullptr, T val = T(0)):pre(pre), next(next), val(val) {}
        void Clear() { // 通过头指针删除整条链表
            if (next) next->Clear(); // 如果存在右节点，递归删除
            delete next;
            next = nullptr;
        }
    } *head, *tail; // 为链表新建头指针和尾指针
    int length; // 链表的当前长度
public:
    List() {
        length = 0, tail = new Node(head = new Node()), head->next = tail; // 初始情况下链表为空，头指针和尾指针相互连接
    }
    List(const List &list) { // 拷贝函数
        length = list.length, tail = new Node(head = new Node());
        Node *cur = head, *pre = head; //
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
        Node *cur = nullptr, *tmp = nullptr; // cur
        if (~index) { // 这里等价于 if (index != -1)
            cur = head->next;
            for (int cnt = 0; cnt < index && cur->next; cur = cur->next, cnt++);
        } else cur = tail->pre->next; // 如果没有填写要插入的位置，默认插入到表尾
        tmp = cur->pre;
        cur->pre = tmp->next = new Node(tmp, cur, val);
        length++;
        return true;
    }
    bool remove(T val) { // 删除链表中键值为val的元素
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
    T operator [] (int index) { // 类似于对数组进行访问
        if (index >= length || index < 0) exit(1);
        int cnt = 0;
        Node *cur = head->next;
        while (cur->next && cnt++ < index) cur = cur->next;
        return cur->val;
    }
    friend std::ostream & operator << (std::ostream &os, const List &tmp) { // 重载流输出
        Node *cur = tmp.head->next;
        while (cur->next->next) os << cur->val << ' ', cur = cur->next;
        os << cur->val;
        return os;
    }
    List operator | (const List &list) const { // 求并集(两个链表中元素均为集合)
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
    List operator & (List const &list) const { // 求交集(两个链表中元素均为集合)
        List ret;
        for (Node *a = list.head->next; a->next; a = a->next)
            for (Node *b = this->head->next; b->next; b = b->next)
                if (b->val == a->val) {
                    ret.insert(a->val);
                    break;
                }
        return ret;
    }
    List sort() { // 对链表中元素进行排序，数据类型T需要拥有小于号
        List ret;
        T tmp[this->length + 7];
        int cnt = 0;
        for (Node *cur = this->head->next; cur->next; cur = cur->next) tmp[cnt++] = cur->val;
        std::sort(tmp, tmp + this->length);
        for (int i = 0; i < cnt; i++) ret.insert(tmp[i]);
        return ret;
    }
    int index(T val) { // 返回从头至尾发现的第一个val的下标
        int index = 0;
        for (Node *cur = head->next; cur->next; cur = cur->next, index++) if (cur->val == val) return index;
        return -1;
    }
};

#endif //TEST_LIST_H
