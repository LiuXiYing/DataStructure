#include <iostream>
#include "stack.h"

// ---------- 括号匹配辅助函数 ----------
bool match(char l, char r) {
    return (l == '(' && r == ')') ||
           (l == '[' && r == ']') ||
           (l == '{' && r == '}');
}

// ---------- 作业要求的 paren 函数（补全部分） ----------
bool paren(const char exp[], Rank lo, Rank hi) {
    Stack<char> S;
    for (Rank i = lo; i < hi; ++i) {
        char c = exp[i];
        if (c == '(' || c == '[' || c == '{') {
            S.push(c);                    // 遇到左括号，压栈
        } else if (c == ')' || c == ']' || c == '}') {
            if (S.empty()) return false;  // 栈空，没有左括号可配
            if (!match(S.top(), c)) return false; // 种类不匹配
            S.pop();                      // 匹配成功，弹出
        }
        // 其他字符（字母、空格等）忽略
    }
    return S.empty();   // 扫描结束后栈必须为空
}

// ---------- 栈的基本测试（作业 3.3 要求） ----------
void testStack() {
    Stack<int> S;
    std::cout << "empty = " << S.empty() << ", size = " << S.size() << std::endl;

    S.push(10);
    S.push(20);
    S.push(30);
    std::cout << "top = " << S.top() << ", size = " << S.size() << std::endl;

    S.top() = 35;  // 修改栈顶
    std::cout << "changed top = " << S.top() << std::endl;

    std::cout << "pop: ";
    while (!S.empty()) {
        std::cout << S.pop() << " ";
    }
    std::cout << std::endl;

    // 测试扩容（压入 8 个元素，观察容量变化）
    for (int i = 1; i <= 8; ++i) S.push(i);
    std::cout << "after growth: ";
    while (!S.empty()) {
        std::cout << S.pop() << " ";
    }
    std::cout << std::endl;

    // 弹空后复用
    S.push(-7);
    std::cout << "reuse = " << S.top() << ", empty = " << S.empty() << std::endl;
    std::cout << "char pop: ";
    Stack<char> C;
    C.push('(');
    C.push('[');
    std::cout << C.pop() << " " << C.pop() << std::endl;
}

// ---------- 括号匹配测试 ----------
bool testParen(const char exp[], Rank lo, Rank hi, bool expected) {
    bool actual = paren(exp, lo, hi);
    std::cout << "actual = " << actual << ", expected = " << expected
              << (actual == expected ? " PASS" : " FAIL") << std::endl;
    return actual == expected;
}

int main() {
    testStack();
    std::cout << std::endl;

    int passed = 0;

    // 15 组固定测试（覆盖空区间、嵌套、并列、种类错误、顺序错误、多余括号、子区间等）
    passed += testParen("{a+[b*(c-d)]}", 0, 13, true);   // 长度 13，不是 14
    passed += testParen("()[]{}", 0, 6, true);
    passed += testParen("a + b", 0, 5, true);
    passed += testParen("", 0, 0, true);
    passed += testParen("([)]", 0, 4, false);
    passed += testParen(")(", 0, 2, false);
    passed += testParen("(()", 0, 3, false);
    passed += testParen("[{()}]", 0, 6, true);
    passed += testParen("((()))", 0, 6, true);
    passed += testParen("{[}]", 0, 4, false);
    passed += testParen("(())", 0, 4, true);
    passed += testParen("()(", 0, 3, false);
    passed += testParen(")()", 0, 3, false);
    passed += testParen("abc(def)ghi", 3, 8, true);      // 注意长度为11，下标3到8是"(def)"
    passed += testParen("{a+[b*(c-d)]}", 0, 12, false);  // 故意截掉最后一个"}"，应false
    std::cout << std::endl;
    std::cout << "paren tests: " << passed << "/15 passed" << std::endl;

    return (passed == 15) ? 0 : 1;
}