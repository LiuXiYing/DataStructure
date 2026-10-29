#ifndef BINNODE_H
#define BINNODE_H

/* 学生完成：仿照课堂示例，定义二叉树节点的模板。
 * 整个文件只允许出现这一个模板 struct：三个数据成员加两个构造函数。 */
template <typename T>
struct BinNode {
    T data;
    BinNode* lc;
    BinNode* rc;
    
    BinNode() : lc(nullptr), rc(nullptr) {}

    BinNode(T e) : data(e), lc(nullptr), rc(nullptr) {}
};

#endif
