#ifndef BINNODE_H
#define BINNODE_H

template <typename T>
struct BinNode {
    /* TODO 1: 三个数据成员 */
    T data;             // 元素本身
    BinNode<T>* lc;     // 左孩子指针
    BinNode<T>* rc;     // 右孩子指针

    /* TODO 2: 默认构造函数，两个孩子置空 */
    BinNode() : lc(nullptr), rc(nullptr) {}

    /* TODO 3: 由元素 e 构造的构造函数 */
    BinNode(const T& e) : data(e), lc(nullptr), rc(nullptr) {}
};

#endif