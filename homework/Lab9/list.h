#ifndef LIST_H
#define LIST_H

/* 按邓俊辉《数据结构（C++ 语言版）》List / ListNode 的命名与组织方式编写的教学子集。
 * 教师提供：本实验不要求修改。双向链表使用头、尾两个哨兵。
 * 仅保留队列需要的基础操作；不含查找、排序、去重与深拷贝。
 * 元素须可默认构造、可复制；本实验使用 int、char、Customer。
 * 调用者须保证节点属于本表且不是哨兵；接口约定见 Lab9.md 的 2.2。
 */
typedef int Rank;                    /* 用整数表示元素个数、下标和窗口编号 */
#define ListNodePosi(T) ListNode<T>*  /* 课本记法：元素类型为 T 的节点指针 */

template <typename T>
struct ListNode {
    T data;                         /* 真实节点保存的元素；哨兵的 data 不使用 */
    ListNodePosi(T) pred;            /* 前驱：沿此指针向表头方向移动 */
    ListNodePosi(T) succ;            /* 后继：沿此指针向表尾方向移动 */

    /* 哨兵也使用这个节点类型，默认构造时先把两个方向的指针置空。 */
    ListNode() : data(), pred(nullptr), succ(nullptr) {}
    /* 创建真实节点时，同时记录元素及它将连接的前驱、后继。 */
    ListNode(const T& e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
        : data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred(const T& e);  /* 在当前节点之前插入 */
    ListNodePosi(T) insertAsSucc(const T& e);  /* 在当前节点之后插入 */
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T& e) {
    /* 原来：pred <-> this；插入后：原 pred <-> x <-> this。
     * 新节点先指向两侧，再让两侧指向新节点；要求当前节点存在前驱。
     */
    ListNodePosi(T) x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e) {
    /* 原来：this <-> succ；插入后：this <-> x <-> 原 succ。
     * 这里只负责接链，节点总数由 List 的插入接口统一更新。
     */
    ListNodePosi(T) x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template <typename T>
class List {
private:
    Rank _size;                    /* 仅统计真实节点，不包含哨兵 */
    ListNodePosi(T) header;         /* 头哨兵，始终位于所有真实节点之前 */
    ListNodePosi(T) trailer;        /* 尾哨兵，始终位于所有真实节点之后 */

    void init();

public:
    List() { init(); }
    ~List();

    /* 本实验不练习深拷贝；禁止默认浅拷贝，避免重复释放同一批节点。 */
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }
    /* 空表的 first() 是 trailer，last() 是 header，均不是 nullptr。
     * 因而读取元素之前要用 empty() 判空，不能只检查节点指针是否非空。
     */
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return trailer->pred; }
    ListNodePosi(T) insertAsFirst(const T& e);
    ListNodePosi(T) insertAsLast(const T& e);
    T remove(ListNodePosi(T) p);    /* p 必须是本表中尚未删除的真实节点 */
    int clear();                   /* 返回删除的真实节点数，保留两个哨兵 */
};

template <typename T>
void List<T>::init() {
    /* 空表也有两个哨兵：header <-> trailer。
     * 节点构造函数已使 header->pred、trailer->succ 为 nullptr。
     */
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

template <typename T>
List<T>::~List() {
    /* 先释放所有真实节点，再释放哨兵；队列析构时也会执行基类析构。 */
    clear();
    delete header;
    delete trailer;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e) {
    /* 在头哨兵之后插入。即使是空表，头哨兵仍有后继可供接链。 */
    ListNodePosi(T) x = header->insertAsSucc(e);
    ++_size;
    return x;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(const T& e) {
    /* 在尾哨兵之前插入，就是尾插；Queue 的 enqueue 将复用此接口。 */
    ListNodePosi(T) x = trailer->insertAsPred(e);
    ++_size;
    return x;
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
    T e = p->data;                  /* 删除节点之前，先保存其中的元素 */
    /* 让 p 两侧的节点互相连接，从链条中跳过 p。
     * 如果 p 是唯一的真实节点，这两步恰好让头、尾哨兵重新相连。
     */
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;                      /* 此后不能再访问 p，也不能返回 p->data 的引用 */
    --_size;
    return e;
}

template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    /* 每次删除当前首节点；remove 会同步减少 _size，直到表空为止。 */
    while (_size > 0) remove(first());
    return oldSize;
}

#endif
