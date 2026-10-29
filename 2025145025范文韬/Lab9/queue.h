#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

/* 学生完成：按课本方式从 List<T> 公有派生，不增加数据成员。
 * 约定链表首端为队首、末端为队尾：尾部入队，首部出队，实现先进先出。
 * 节点、计数和内存释放均由 List 管理，Queue 只限制日常操作的位置。
 * size()、empty() 直接继承即可，无需重新实现构造、析构或计数器。
 */
template <typename T>
class Queue : public List<T> {
public:
    void enqueue(const T& e);    /* 从队尾入队 */
    T dequeue();                /* 删除并返回队首元素，前提：非空 */
    T& front();                 /* 返回队首元素的引用，前提：非空 */
};

template <typename T>
void Queue<T>::enqueue(const T& e) {
    /* 队尾即链表末端，直接复用基类的尾插接口，节点数与接链都由 List 维护。 */
    this->insertAsLast(e);
}

template <typename T>
T Queue<T>::dequeue() {
    /* 队首即链表首端；remove 在删除前保存元素并返回其值。 */
    return this->remove(this->first());
}

template <typename T>
T& Queue<T>::front() {
    /* first() 给出首节点指针，取其 data 的引用返回，不删除节点。 */
    return this->first()->data;
}

#endif
