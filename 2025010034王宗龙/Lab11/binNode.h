#ifndef BINNODE_H
#define BINNODE_H

/* 二叉树节点的模板定义（仿照课堂示例的二叉链表写法）：
 * 整个文件只允许出现这一个模板 struct：三个数据成员加两个构造函数。 */
template <typename T>
struct BinNode {
    /* 三个数据成员：元素本身（类型 T）、左孩子指针、右孩子指针。 */
    T data;
    BinNode* lc;
    BinNode* rc;

    /* 默认构造函数：把两个孩子指针置为 nullptr，data 保持默认值。 */
    BinNode() : lc(nullptr), rc(nullptr) {}

    /* 由元素 e 构造的构造函数：同样把两个孩子指针置为 nullptr。 */
    BinNode(const T& e) : data(e), lc(nullptr), rc(nullptr) {}

};

#endif
