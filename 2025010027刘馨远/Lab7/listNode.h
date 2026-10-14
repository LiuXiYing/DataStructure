#ifndef LISTNODE_H
#define LISTNODE_H

/*
 * 邓俊辉《数据结构（C++ 语言版）》第三章：列表结点
 * 本文件与 list.h 合起来，就是课本里链表的那一对文件
 */

template <typename T>
struct ListNode {
    T data;                 // 数据域
    ListNode<T>* pred;      // 前驱指针
    ListNode<T>* succ;      // 后继指针

    // 教师提供：默认构造函数，两个指针都置空
    ListNode()
        : data(), pred(nullptr), succ(nullptr) {}

    // 教师提供：带数据的构造函数
    ListNode(const T& e,
             ListNode<T>* p = nullptr,
             ListNode<T>* s = nullptr)
        : data(e), pred(p), succ(s) {}

    // 练习 1：在自己前面插入 e，返回新结点
    ListNode<T>* insertAsPred(const T& e);
    // 练习 2：在自己后面插入 e，返回新结点
    ListNode<T>* insertAsSucc(const T& e);
};

// 练习 1：在自己前面插入 e
template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, this->pred, this); // 新结点先抓住两边
    this->pred->succ = x;  // 老前驱的后继改成 x
    this->pred = x;        // this 的前驱改成 x
    return x;
}

// 练习 2：在自己后面插入 e
template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T& e) {
    ListNode<T>* x = new ListNode<T>(e, this, this->succ); // 新结点先抓住两边
    this->succ->pred = x;  // 老后继的前驱改成 x
    this->succ = x;        // this 的后继改成 x
    return x;
}

#endif