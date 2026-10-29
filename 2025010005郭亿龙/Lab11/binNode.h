#ifndef BINNODE_H
#define BINNODE_H

/* 二叉树的二叉链表节点：一个模板 struct，三个数据成员加两个构造函数。 */
template <typename T>
struct BinNode {
    T data;          /* 元素本身，类型为 T */
    BinNode<T>* lc;  /* 指向左孩子的指针，无左孩子时为 nullptr */
    BinNode<T>* rc;  /* 指向右孩子的指针，无右孩子时为 nullptr */

    /* 默认构造函数：把两个孩子指针置为 nullptr，data 保持默认值。 */
    BinNode() : data(), lc(nullptr), rc(nullptr) {}

    /* 由元素 e 构造：同样把两个孩子指针置为 nullptr。 */
    BinNode(const T& e) : data(e), lc(nullptr), rc(nullptr) {}
};

#endif
