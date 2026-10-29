#include <iostream>
#include <queue>  /* 层次遍历使用，与课堂示例一致 */

#include "binNode.h"

using Node = BinNode<char>;

/* 先序遍历 (根 -> 左 -> 右) */
void preorder(Node* root) {
    if (root == nullptr) return; // 递归出口
    std::cout << root->data << ' '; // 访问根
    preorder(root->lc);             // 访问左子树
    preorder(root->rc);             // 访问右子树
}

/* 中序遍历 (左 -> 根 -> 右) */
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->lc);              // 访问左子树
    std::cout << root->data << ' '; // 访问根
    inorder(root->rc);              // 访问右子树
}

/* 后序遍历 (左 -> 右 -> 根) */
void postorder(Node* root) {
    if (root == nullptr) return;
    postorder(root->lc);            // 访问左子树
    postorder(root->rc);            // 访问右子树
    std::cout << root->data << ' '; // 访问根
}
/* 学生完成：层次遍历，借助先进先出队列实现，访问即输出。 */
void levelOrder(Node* root) {
    if (root == nullptr) return; // 1. 空树直接返回

    std::queue<Node*> q;
    q.push(root);                // 根节点入队

    while (!q.empty()) {
        Node* current = q.front(); // 2. 取出队头
        q.pop();                   // 队头出队
        std::cout << current->data << ' '; // 访问该节点

        // 3. 依次把左右孩子入队（如果存在）
        if (current->lc != nullptr) {
            q.push(current->lc);
        }
        if (current->rc != nullptr) {
            q.push(current->rc);
        }
    }
}
/* 教师提供：按“先左右子树、后根”的顺序释放整棵树，调用一次即可避免内存泄漏。 */
void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    destroyTree(root->lc);
    destroyTree(root->rc);
    delete root;
}

int main() {
    /* TODO 5: 按 Lab11.md 第三节的树形图手动创建指定的二叉树,
     * 根节点指针命名为 root，供下方的输出框架使用。
     * 第一步逐个 new 节点；第二步给 data 赋值；第三步连接 lc / rc。 */

    // ----- 替换开始 -----
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');

    A->lc = B; A->rc = C;
    B->lc = D; B->rc = E;
    C->lc = nullptr;
    C->rc = F;

    Node* root = A;
    // ----- 替换结束 -----


    /* 以下输出框架由教师提供... */
    std::cout << "先序遍历（根-左-右）：";
    preorder(root);
    std::cout << '\n';

    std::cout << "中序遍历（左-根-右）：";
    inorder(root);
    std::cout << '\n';

    std::cout << "后序遍历（左-右-根）：";
    postorder(root);
    std::cout << '\n';

    std::cout << "层次遍历（从上到下、从左到右）：";
    levelOrder(root);
    std::cout << '\n';

    destroyTree(root);
    return 0;
}
