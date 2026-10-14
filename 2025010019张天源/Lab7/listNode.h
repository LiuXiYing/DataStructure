#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;

    ListNode() : data(), pred(nullptr), succ(nullptr) {}
    ListNode(const T& e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr)
        : data(e), pred(p), succ(s) {}

    ListNode<T>* insertAsPred(const T& e);
    ListNode<T>* insertAsSucc(const T& e);
};

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

#endif