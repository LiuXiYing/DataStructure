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
    /* 栈顶即向量末端：在秩 size() 处插入，等于末尾追加。 */
    this->insert(this->size(), e);
}

template <typename T>
T Stack<T>::pop() {
    /* 删除末元素（秩 size()-1）并返回其值；调用者保证栈非空。 */
    return this->remove(this->size() - 1);
}

template <typename T>
T& Stack<T>::top() {
    /* 返回末元素的引用，栈的大小不变；调用者保证栈非空。 */
    return Vector<T>::operator[](this->size() - 1);
}

#endif
