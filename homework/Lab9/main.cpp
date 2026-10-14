#include <iostream>
#include "queue.h"

/* 教师提供：使用队列接口检查内容，检查后队列被清空。
 * expected 只保存预期值，n 是预期元素数；测试本身也不直接访问链表节点。
 */
template <typename T>
bool expectContents(Queue<T>& Q, const T expected[], Rank n) {
    bool ok = Q.size() == n;
    Rank i = 0;
    while (!Q.empty()) {
        T value = Q.dequeue();
        /* || 从左向右短路：实际元素过多时，不访问越界的 expected[i]。 */
        if (i >= n || value != expected[i]) {
            ok = false;
        }
        ++i;
    }
    return ok && i == n && Q.size() == 0;  /* 同时核对值、元素个数和清空后的状态 */
}

/* 打印单组结果并返回判断值，让 main 能累计通过的组数。 */
bool check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
    return ok;
}

/* 以下测试与 main 由教师提供，不得修改。 */
int main() {
    int passed = 0;
    Queue<int> Q;
    /* 第 1～5 组：从空队列开始，验证尾入首出，以及 front 返回可写引用。 */
    if (check("empty queue", Q.empty() && Q.size() == 0)) {
        ++passed;
    }

    Q.enqueue(10);
    Q.enqueue(20);
    Q.enqueue(30);
    if (check("enqueue and front", Q.size() == 3 && !Q.empty() && Q.front() == 10)) {
        ++passed;
    }
    if (!Q.empty()) {
        Q.front() = 15;
    }
    if (check("writable front", Q.size() == 3 && !Q.empty() && Q.front() == 15)) {
        ++passed;
    }
    if (check("dequeue oldest", !Q.empty() && Q.dequeue() == 15 && Q.size() == 2)) {
        ++passed;
    }
    const int rest[] = {20, 30};
    if (check("FIFO order", expectContents(Q, rest, 2))) {
        ++passed;
    }

    /* 第 6 组：出队至空后，哨兵仍在，队列应能继续使用。 */
    Q.enqueue(-7);
    const int one[] = {-7};
    if (check("reuse after empty", expectContents(Q, one, 1))) {
        ++passed;
    }

    /* 第 7 组：中途出队后再入队，检查新元素仍排在已有元素之后。 */
    Q.enqueue(1);
    Q.enqueue(2);
    bool firstRemoved = !Q.empty() && Q.dequeue() == 1;
    Q.enqueue(3);
    Q.enqueue(4);
    const int mixed[] = {2, 3, 4};
    bool mixedOrder = expectContents(Q, mixed, 3);
    if (check("interleaved operations", firstRemoved && mixedOrder)) {
        ++passed;
    }

    /* 第 8 组：重复值、零和负数都应作为普通元素保留。 */
    const int repeats[] = {0, -1, -1, 0};
    for (Rank i = 0; i < 4; ++i) {
        Q.enqueue(repeats[i]);
    }
    if (check("duplicates and zero", expectContents(Q, repeats, 4))) {
        ++passed;
    }

    /* 第 9 组：以队首元素的引用作为入队实参，应复制出一个新元素。 */
    Q.enqueue(42);
    if (!Q.empty()) {
        Q.enqueue(Q.front());
    }
    const int alias[] = {42, 42};
    if (check("enqueue from front reference", expectContents(Q, alias, 2))) {
        ++passed;
    }

    /* 第 10 组：反复经过“空表 → 单节点 → 空表”，检查边界接链。 */
    bool reused = true;
    for (int i = 0; i < 20; ++i) {
        Q.enqueue(i);
        if (Q.size() != 1 || Q.empty()) {
            reused = false;
        }
        if (!Q.empty() && Q.dequeue() != i) {
            reused = false;
        }
        if (!Q.empty() || Q.size() != 0) {
            reused = false;
        }
    }
    if (check("repeated single element", reused)) {
        ++passed;
    }

    /* 第 11 组：连续入队、出队较多元素，核对完整顺序和计数。 */
    int many[100];                    /* 仅保存测试的预期值，不用于实现队列 */
    for (Rank i = 0; i < 100; ++i) {
        many[i] = i;
        Q.enqueue(i);
    }
    if (check("100 elements", expectContents(Q, many, 100))) {
        ++passed;
    }

    /* 第 12 组：换用 char，确认 Queue<T> 没有把元素类型写死为 int。 */
    Queue<char> C;
    C.enqueue('A');
    C.enqueue('B');
    C.enqueue('C');
    const char letters[] = {'A', 'B', 'C'};
    if (check("char queue", expectContents(C, letters, 3))) {
        ++passed;
    }

    std::cout << "queue tests: " << passed << "/12 passed\n";
    return passed == 12 ? 0 : 1;     /* 退出码供 CTest 判断整个目标是否通过 */
}
