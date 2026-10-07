#include <cstdlib>
#include <iostream>
#include "queue.h"

/* 一个窗口对应一个队列：队首正在服务，其余顾客按到达顺序等待。
 * 程序用循环推进模拟时间；“多个窗口同时服务”不需要线程或真实等待。
 */
/* 沿用教材字段：所属窗口，以及尚需服务的时间；入队时 time 必须大于 0。 */
struct Customer {
    int window;                    /* 所属窗口编号，范围为 0 到 nWin - 1 */
    unsigned int time;             /* 剩余服务时间，不是到达时间或等待时间 */
};

/* 学生完成：nWin > 0；按人数选最短队列，同长时选编号最小的窗口。 */
int bestWindow(Queue<Customer> windows[], Rank nWin) {
    /* TODO 5：从窗口 0 开始，只在发现严格更短的队列时更新候选窗口。
     * 队列长度包括正在服务的队首顾客，不比较服务时长。
     * nWin > 0，因此窗口 0 可以作为初始候选；仍需扫描后续所有窗口。
     * 相等时保留原候选，才能让编号较小的窗口优先。
     */
}

/* 学生完成：推进一个时间单位，返回本次完成服务并出队的顾客总数。 */
int serveOneTick(Queue<Customer> windows[], Rank nWin) {
    /* TODO 6：依次检查每个窗口。
     * 非空时，把队首顾客的 time 减 1；减到 0 时出队，并累计完成数量。
     * 每个窗口在本次调用中最多服务一个顾客，不能继续给新队首减时间。
     * 必须通过 front() 的引用修改队内顾客，不能只修改局部副本。
     * 先判空再读取队首；在队顾客的 time 为正，递减后不会发生无符号下溢。
     * 一旦出队，原队首的引用便失效，不要再通过该引用访问顾客。
     */
}

/* 教师提供：time == 0 表示本时刻没有新顾客，返回 -1；否则返回加入的窗口。 */
int enqueueArrival(Queue<Customer> windows[], Rank nWin, unsigned int time) {
    if (time == 0) return -1;       /* 0 是“无人到达”的标记，不能作为顾客入队 */
    Customer c;
    c.time = time;
    c.window = bestWindow(windows, nWin);  /* 按入队之前各窗口的人数选择 */
    windows[c.window].enqueue(c);
    return c.window;
}

/* 输出单组测试结果，并把结果交给调用者累计通过数。 */
bool check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
    return ok;
}

/* 教师提供：不删除顾客，只核对人数和队首；空窗口不访问 front()。 */
bool expectWindow(Queue<Customer>& Q, int window, Rank size, unsigned int time) {
    if (Q.size() != size) return false;
    if (size == 0) return Q.empty(); /* 此时 time 只是占位实参，不能读取队首 */
    return !Q.empty() && Q.front().window == window && Q.front().time == time;
}

/* 固定到达表：每项为该时刻新顾客需要的服务时间，0 表示无人到达。 */
const unsigned int FIXED_ARRIVALS[] = {3, 2, 4, 1, 2, 0};
const Rank FIXED_TICKS = 6;

/* 逐轮核对固定模拟：既检查窗口选择和离开人数，也检查服务后的窗口状态。 */
bool testFixedTimeline() {
    Queue<Customer> windows[2];
    const int expectedWindow[] = {0, 1, 0, 1, 1, -1};
    const int expectedServed[] = {0, 0, 2, 1, 0, 1};
    /* 二维数组的行是 now，列是窗口编号；所有值均对应本轮服务结束后。
     * 这些数组只保存预期答案，不参与窗口选择或服务计算。
     */
    const Rank expectedSize[6][2] = {{1, 0}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 0}};
    const unsigned int expectedTime[6][2] = {{2, 0}, {1, 1}, {4, 0}, {3, 0}, {2, 1}, {1, 0}};
    int arrived = 0, served = 0;
    bool ok = true;
    for (Rank now = 0; now < FIXED_TICKS; ++now) {
        /* 与 simulate 一致：先到达，再服务，最后核对本轮结果。 */
        int chosen = enqueueArrival(windows, 2, FIXED_ARRIVALS[now]);
        if (chosen >= 0) ++arrived;
        int finished = serveOneTick(windows, 2);
        served += finished;
        if (chosen != expectedWindow[now] || finished != expectedServed[now]) ok = false;
        for (Rank i = 0; i < 2; ++i)
            if (!expectWindow(windows[i], i, expectedSize[now][i], expectedTime[now][i])) ok = false;
    }
    return ok && arrived == 5 && served == 4 && windows[0].size() + windows[1].size() == 1;
}

/* 以下统一测试不得修改。 */
int testBank() {
    int passed = 0;
    Queue<Customer> windows[3];
    /* 先验证窗口选择：空窗口、单窗口、长度相等及人数与时长的区别。 */
    if (check("empty windows choose 0", bestWindow(windows, 3) == 0)) ++passed;
    windows[0].enqueue(Customer{0, 5});
    if (check("single window", bestWindow(windows, 1) == 0)) ++passed;
    windows[1].enqueue(Customer{1, 9});
    if (check("choose empty window", bestWindow(windows, 3) == 2)) ++passed;
    windows[2].enqueue(Customer{2, 1});
    if (check("equal lengths choose 0", bestWindow(windows, 3) == 0)) ++passed;
    windows[0].enqueue(Customer{0, 1});
    if (check("shortest queue, not shortest time", bestWindow(windows, 3) == 1)) ++passed;

    {
        /* 三个窗口人数依次为 3、2、1，防止找到首个更短队列就提前返回。 */
        Queue<Customer> decreasing[3];
        for (Rank i = 0; i < 3; ++i)
            for (Rank j = 0; j < 3 - i; ++j) decreasing[i].enqueue(Customer{i, 1});
        if (check("scan all windows", bestWindow(decreasing, 3) == 2)) ++passed;
    }

    /* 每个非空窗口各服务一次；窗口 2 的顾客恰好完成，其余顾客时间减 1。 */
    int finished = serveOneTick(windows, 3);
    bool parallel = finished == 1 && expectWindow(windows[0], 0, 2, 4)
                    && expectWindow(windows[1], 1, 1, 8) && expectWindow(windows[2], 2, 0, 0);
    if (check("parallel service", parallel)) ++passed;
    finished = serveOneTick(windows, 3);
    bool nextTick = finished == 0 && expectWindow(windows[0], 0, 2, 3)
                    && expectWindow(windows[1], 1, 1, 7) && expectWindow(windows[2], 2, 0, 0);
    if (check("skip empty window", nextTick)) ++passed;

    /* 同一窗口的旧队首离开后，新队首必须等到下一轮才能开始服务。 */
    Queue<Customer> single[1];
    single[0].enqueue(Customer{0, 1});
    single[0].enqueue(Customer{0, 3});
    finished = serveOneTick(single, 1);
    if (check("successor waits until next tick", finished == 1 && expectWindow(single[0], 0, 1, 3))) ++passed;
    finished = serveOneTick(single, 1);
    if (check("modify customer in queue", finished == 0 && expectWindow(single[0], 0, 1, 2))) ++passed;

    /* 两个窗口可以在同一轮各完成一人；全部空闲时完成数应为 0。 */
    Queue<Customer> pair[2];
    pair[0].enqueue(Customer{0, 1});
    pair[1].enqueue(Customer{1, 1});
    finished = serveOneTick(pair, 2);
    if (check("simultaneous departures", finished == 2 && pair[0].empty() && pair[1].empty())) ++passed;
    finished = serveOneTick(pair, 2);
    if (check("all windows idle", finished == 0 && pair[0].empty() && pair[1].empty())) ++passed;
    if (check("fixed arrival timeline", testFixedTimeline())) ++passed;

    std::cout << "bank tests: " << passed << "/13 passed\n";
    return passed;
}

/* 教师提供：nullptr 使用教材的随机到达规则；非空指针使用固定到达表。
 * 前提：nWin > 0，servTime >= 0；固定表至少有 servTime 项。
 */
void simulate(Rank nWin, Rank servTime, const unsigned int arrivals[] = nullptr) {
    /* 分别构造 nWin 个独立队列，每个队列有自己的哨兵和节点计数。 */
    Queue<Customer>* windows = new Queue<Customer>[nWin];
    int arrived = 0, served = 0;     /* 累计到达人数、累计完成服务人数 */
    /* 一轮对应 [now, now + 1)：区间开始时到达，区间内接受一个单位服务。
     * 新顾客若直接成为队首，本轮就可以接受服务；营业结束后不再推进时间。
     */
    for (Rank now = 0; now < servTime; ++now) {
        unsigned int time = 0;
        if (arrivals != nullptr) {
            time = arrivals[now];  /* 固定表：正数是服务时长，0 表示本轮无人到达 */
        } else if (std::rand() % (1 + nWin)) {
            /* 教材随机规则：非零时到达一人，所需服务时间在 1～98 之间。 */
            time = 1 + std::rand() % 98;
        }
        int chosen = enqueueArrival(windows, nWin, time);  /* A：先到达、选队并入队 */
        if (chosen >= 0) ++arrived;
        int finished = serveOneTick(windows, nWin);       /* B：再让每个窗口服务一次 */
        served += finished;                              /* C：本时刻服务结束 */
        /* 下列记录都是服务结束后的状态；finished 仅表示本轮完成数。 */
        std::cout << "t=" << now << " arrival=" << time << " window=" << chosen
                  << " served=" << finished;
        for (Rank i = 0; i < nWin; ++i) {
            std::cout << " | W" << i << " size=" << windows[i].size();
            if (!windows[i].empty()) std::cout << " front=" << windows[i].front().time;
            else std::cout << " front=-";  /* 空窗口没有有效队首，使用 - 表示 */
        }
        std::cout << '\n';
    }
    int remaining = 0;
    /* 尚在队列中的人数包括正在服务者和等待者；应满足 arrived = served + remaining。 */
    for (Rank i = 0; i < nWin; ++i) remaining += windows[i].size();
    std::cout << "arrived=" << arrived << ", served=" << served << ", remaining=" << remaining << '\n';
    delete[] windows;              /* 下班后不再服务；析构清理剩余节点，不算服务完成 */
}

int main() {
    if (testBank() != 13) return 1;       /* 测试失败时不继续演示 */
    /* 先运行便于逐行核对的固定场景，再运行教材风格的随机场景。 */
    std::cout << "\nFixed simulation: 2 windows, 6 ticks\n";
    simulate(2, FIXED_TICKS, FIXED_ARRIVALS);
    std::cout << "\nRandom simulation: 3 windows, 20 ticks\n";
    std::srand(2026);                    /* 同一实现可复现；不同标准库的序列可能不同 */
    simulate(3, 20);
    return 0;
}
