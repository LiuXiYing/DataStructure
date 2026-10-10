#ifndef LAB7_LIST_H
#define LAB7_LIST_H
#include <iostream>
#include "listNode.h"

typedef int Rank;

template <typename T>
class List {
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;

protected:
    void init();
    int clear();

public:
    List() { init(); }
    ~List();

    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }
    ListNode<T>* first() const { return header->succ; }
    ListNode<T>* last() const { return trailer->pred; }
    bool valid(ListNode<T>* p) const {
        return p != nullptr && p != header && p != trailer;
    }

    ListNode<T>* insertAsFirst(const T& e);
    ListNode<T>* insertAsLast(const T& e);
    ListNode<T>* insertA(ListNode<T>* p, const T& e);
    ListNode<T>* insertB(ListNode<T>* p, const T& e);

    T remove(ListNode<T>* p);

    ListNode<T>* find(const T& e) const;
    ListNode<T>* operator[](Rank r) const;
    Rank rankOf(ListNode<T>* p) const;

    bool insert(Rank r, const T& e);
    bool remove(Rank r, T& e);
    bool get(Rank r, T& e) const;

    void print() const;
    void printReverse() const;
};

/* --------------------------------------------------------------------------
 * 保护接口
 * -------------------------------------------------------------------------- */

template <typename T>
void List<T>::init() {
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

/* 练习 3：删除全部有效结点，保留两个哨兵，返回原来有多少个 */
template <typename T>
int List<T>::clear() {
    int n = _size;
    while (_size > 0) {
        remove(header->succ);
    }
    return n;
}

/* --------------------------------------------------------------------------
 * 构造与析构
 * -------------------------------------------------------------------------- */

template <typename T>
List<T>::~List() {
    int n = clear();
    delete header;
    delete trailer;
    std::cout << "(destructor: cleared " << n << " data nodes, freed 2 sentinels)\n";
}

/* --------------------------------------------------------------------------
 * 插入：四个入口，一条通路
 * -------------------------------------------------------------------------- */

template <typename T>
ListNode<T>* List<T>::insertAsFirst(const T& e) {
    return insertB(first(), e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(const T& e) {
    return insertB(trailer, e);
}

/* 练习 4a：作为 p 的后继插入 */
template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsSucc(e);
}

/* 练习 4b：作为 p 的前驱插入 */
template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsPred(e);
}

/* --------------------------------------------------------------------------
 * 删除
 * -------------------------------------------------------------------------- */

/* 练习 5：删除结点 p，返回它保存的数据 */
template <typename T>
T List<T>::remove(ListNode<T>* p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

/* --------------------------------------------------------------------------
 * 查找与按秩访问
 * -------------------------------------------------------------------------- */

/* 练习 6：按值查找，从末结点往前找，命中"最后一个" */
template <typename T>
ListNode<T>* List<T>::find(const T& e) const {
    for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
        if (p->data == e) {
            return p;
        }
    }
    return nullptr;
}

/* 练习 7：按秩定位，从首结点走 r 步，越界返回 nullptr */
template <typename T>
ListNode<T>* List<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) {
        return nullptr;
    }
    ListNode<T>* p = first();
    while (r-- > 0) {
        p = p->succ;
    }
    return p;
}

template <typename T>
Rank List<T>::rankOf(ListNode<T>* p) const {
    if (!valid(p)) {
        return -1;
    }
    Rank r = 0;
    for (ListNode<T>* q = first(); q != p; q = q->succ) {
        r++;
    }
    return r;
}

/* --------------------------------------------------------------------------
 * 为与 Lab6 的 C 版逐条对照而补的三个接口
 * -------------------------------------------------------------------------- */

/* 练习 8a：对应 C 版 listInsert */
template <typename T>
bool List<T>::insert(Rank r, const T& e) {
    if (r < 0 || r > _size) {
        return false;
    }
    if (r == _size) {
        insertB(trailer, e);
    } else {
        insertB((*this)[r], e);
    }
    return true;
}

/* 练习 8b：对应 C 版 listRemove */
template <typename T>
bool List<T>::remove(Rank r, T& e) {
    if (r < 0 || r >= _size) {
        return false;
    }
    e = remove((*this)[r]);
    return true;
}

/* 练习 8c：对应 C 版 listGet，失败时不修改 e */
template <typename T>
bool List<T>::get(Rank r, T& e) const {
    ListNode<T>* p = (*this)[r];
    if (p == nullptr) {
        return false;
    }
    e = p->data;
    return true;
}

/* --------------------------------------------------------------------------
 * 输出
 * -------------------------------------------------------------------------- */

template <typename T>
void List<T>::print() const {
    std::cout << "[size = " << _size << "] ";
    for (ListNode<T>* p = header->succ; p != trailer; p = p->succ) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}

/* 练习 9：反向遍历 */
template <typename T>
void List<T>::printReverse() const {
    std::cout << "[size = " << _size << "] reverse: ";
    for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}
#endif //LAB7_LIST_H
