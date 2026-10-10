#ifndef STACK_H
#define STACK_H

#include "vector.h"

/* 学生完成：按课本方式从 Vector<T> 公有派生，不增加数据成员。 */
template <typename T>
class Stack : public Vector<T> {
public:
    void push(const T& e);       /* 将 e 压入栈顶 */
    T pop();                    /* 弹出并返回栈顶元素，前提：非空 */
    T& top();                   /* 返回栈顶引用，前提：非空 */
};

template <typename T>
void Stack<T>::push(const T& e) {
    this->insert(e);                        /* 在向量末端追加，等价于压栈 */
}

template <typename T>
T Stack<T>::pop() {
    return this->remove(this->size() - 1);  /* 删除并返回末元素（栈顶） */
}

template <typename T>
T& Stack<T>::top() {
    return Vector<T>::operator[](this->size() - 1);  /* 返回栈顶引用，不删除 */
}

#endif
