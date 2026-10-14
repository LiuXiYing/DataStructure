#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "listNode.h"

typedef int Rank;   // 秩与课本一致

/*
 * 邓俊辉《数据结构（C++ 语言版）》第三章：列表 List
 * 与 Lab6 的 C 版相比，结构性差别有五处：
 *   1. 单链表改成双向链表：结点多了 pred，删除不再需要找前驱
 *   2. 一个头哨兵改成两个哨兵 header / trailer
 *   3. 自由函数 + 结构体指针参数 改成 类 + 成员函数
 *   4. 把 int 换成模板参数 T：同一个类支持 List<int>、List<double>
 *   5. 拆成两个头文件：ListNode 与 List 各自独立
 */

template <typename T>
class List {
private:
    int _size;                  // 有效元素个数
    ListNode<T>* header;        // 头哨兵
    ListNode<T>* trailer;       // 尾哨兵

protected:
    // 教师提供：建立空表
    void init() {
        header = new ListNode<T>();
        trailer = new ListNode<T>();
        header->succ = trailer;
        trailer->pred = header;
        header->pred = nullptr;
        trailer->succ = nullptr;
        _size = 0;
    }

    // 练习 3：删除全部有效结点，保留两个哨兵，返回删除的个数
    int clear() {
        int oldSize = _size;
        while (_size > 0) {
            remove(header->succ);
        }
        return oldSize;
    }

public:
    // 教师提供：构造函数
    List() { init(); }

    // 教师提供：析构函数
    ~List() {
        int n = clear();
        delete header;
        delete trailer;
        std::cout << "(destructor: cleared " << n
                  << " data nodes, freed 2 sentinels)\n";
    }

    /* 只读接口，全部由教师提供 */
    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }
    ListNode<T>* first() const { return header->succ; }
    ListNode<T>* last() const { return trailer->pred; }
    bool valid(ListNode<T>* p) const {
        return p != nullptr && p != header && p != trailer;
    }

    /* 插入：四个入口，最后都汇到同一个地方 */
    // 教师提供
    ListNode<T>* insertAsFirst(const T& e) {
        return insertB(first(), e);
    }
    // 教师提供
    ListNode<T>* insertAsLast(const T& e) {
        return insertB(trailer, e);
    }

    // 练习 4a：作为 p 的后继插入
    ListNode<T>* insertA(ListNode<T>* p, const T& e) {
        _size++;
        return p->insertAsSucc(e);
    }

    // 练习 4b：作为 p 的前驱插入
    ListNode<T>* insertB(ListNode<T>* p, const T& e) {
        _size++;
        return p->insertAsPred(e);
    }

    /* 删除 */
    // 练习 5：删除结点 p，返回它保存的数据
    T remove(ListNode<T>* p) {
        T e = p->data;              // 先取出 data
        p->pred->succ = p->succ;    // 断链
        p->succ->pred = p->pred;
        delete p;                   // 释放
        _size--;
        return e;
    }

    /* 查找与按秩访问 */
    // 练习 6：按值查找，返回结点的位置
    ListNode<T>* find(const T& e) const {
        for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
            if (p->data == e) return p;
        }
        return nullptr;
    }

    // 练习 7：按秩定位，返回秩为 r 的结点，越界返回 nullptr
    ListNode<T>* operator[](Rank r) const {
        if (r < 0 || r >= _size) return nullptr;
        ListNode<T>* p = first();
        for (Rank i = 0; i < r; i++) {
            p = p->succ;
        }
        return p;
    }

    // 教师提供：位置折算成秩
    Rank rankOf(ListNode<T>* p) const {
        if (!valid(p)) return -1;
        Rank r = 0;
        for (ListNode<T>* q = first(); q != p; q = q->succ) {
            r++;
        }
        return r;
    }

    /* 为与 Lab6 的 C 版逐条对照而补的三个接口 */
    // 练习 8a：对应 C 版 listInsert
    bool insert(Rank r, const T& e) {
        if (r < 0 || r > _size) return false;
        ListNode<T>* p = (r == _size) ? trailer : (*this)[r];
        insertB(p, e);
        return true;
    }

    // 练习 8b：对应 C 版 listRemove
    bool remove(Rank r, T& e) {
        if (r < 0 || r >= _size) return false;
        e = remove((*this)[r]);
        return true;
    }

    // 练习 8c：对应 C 版 listGet
    bool get(Rank r, T& e) const {
        if (r < 0 || r >= _size) return false;
        e = (*this)[r]->data;
        return true;
    }

    /* 输出 */
    // 教师提供
    void print() const {
        std::cout << "[size = " << _size << "] ";
        for (ListNode<T>* p = header->succ; p != trailer; p = p->succ) {
            std::cout << p->data << ' ';
        }
        std::cout << '\n';
    }

    // 练习 9：反向遍历
    void printReverse() const {
        std::cout << "[size = " << _size << "] reverse: ";
        for (ListNode<T>* p = trailer->pred; p != header; p = p->pred) {
            std::cout << p->data << ' ';
        }
        std::cout << '\n';
    }
};

#endif