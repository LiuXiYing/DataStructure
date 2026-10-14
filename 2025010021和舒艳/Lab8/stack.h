#ifndef STACK_H
#define STACK_H

#include "vector.h"

template <typename T>
class Stack : public Vector<T> {
public:
    void push(const T& e);
    T pop();
    T& top();
};

// TODO 1: 在向量末尾插入元素
template <typename T>
void Stack<T>::push(const T& e) {
    this->insert(e);
}

// TODO 2: 删除并返回末元素（调用者保证非空）
template <typename T>
T Stack<T>::pop() {
    return this->remove(this->size() - 1);
}

// TODO 3: 返回末元素的引用（调用者保证非空）
template <typename T>
T& Stack<T>::top() {
    return Vector<T>::operator[](this->size() - 1);
}

#endif