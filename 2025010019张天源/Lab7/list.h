#ifndef LIST_H
#define LIST_H

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
    bool valid(ListNode<T>* p) const { return p != nullptr && p != header && p != trailer; }

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

template <typename T>
void List<T>::init() {
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (_size > 0) {
        remove(header->succ);
    }
    return oldSize;
}

template <typename T>
List<T>::~List() {
    int n = clear();
    delete header;
    delete trailer;
    std::cout << " (destructor: cleared " << n << " data nodes, freed 2 sentinels)\n";
}

template <typename T>
ListNode<T>* List<T>::insertAsFirst(const T& e) {
    return insertB(first(), e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(const T& e) {
    return insertB(trailer, e);
}

template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, const T& e) {
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
T List<T>::remove(ListNode<T>* p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
ListNode<T>* List<T>::find(const T& e) const {
    ListNode<T>* p = trailer->pred;
    while (p != header && p->data != e) {
        p = p->pred;
    }
    return (p == header) ? nullptr : p;
}

template <typename T>
ListNode<T>* List<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) return nullptr;
    ListNode<T>* p = first();
    for (Rank i = 0; i < r; i++) {
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

template <typename T>
bool List<T>::insert(Rank r, const T& e) {
    if (r < 0 || r > _size) return false;
    ListNode<T>* p = (r == _size) ? trailer : (*this)[r];
    insertB(p, e);
    return true;
}

template <typename T>
bool List<T>::remove(Rank r, T& e) {
    if (r < 0 || r >= _size) return false;
    ListNode<T>* p = (*this)[r];
    e = remove(p);
    return true;
}

template <typename T>
bool List<T>::get(Rank r, T& e) const {
    ListNode<T>* p = (*this)[r];
    if (p == nullptr) return false;
    e = p->data;
    return true;
}

template <typename T>
void List<T>::print() const {
    std::cout << "[size = " << _size << "] ";
    for (ListNode<T>* p = header->succ; p != trailer; p = p->succ) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void List<T>::printReverse() const {
    std::cout << "[size = " << _size << "] reverse: ";
    for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
        std::cout << p->data << ' ';
    }
    std::cout << '\n';
}

#endif