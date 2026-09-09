#include <stdio.h>

// O(1)
long long algorithm1(int n) {
    long long count = 0;
    count++;
    return count;
}

// O(n)
long long algorithm2(int n) {
    long long count = 0;
    for(int i = 0; i < n; i++) {
        count++;
    }
    return count;
}

// O(n^2)
long long algorithm3(int n) {
    long long count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            count++;
        }
    }
    return count;
}

// O(n log n) 就是刚才题目里的algorithm4
long long algorithm4(int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            count++;
        }
    }
    return count;
}

int main(void) {
    // 输入规模数组：2048,4096,8192,16384
    int sizes[] = {2048, 4096, 8192, 16384};
    int len = sizeof(sizes) / sizeof(sizes[0]);

    // 打印表头
    printf("%-8s %-15s %-15s %-15s %-15s\n", "n", "algorithm1", "algorithm2", "algorithm3", "algorithm4");

    // 循环完成4组测试，不重复复制代码
    for(int idx = 0; idx < len; idx++) {
        int n = sizes[idx];
        long long a1 = algorithm1(n);
        long long a2 = algorithm2(n);
        long long a3 = algorithm3(n);
        long long a4 = algorithm4(n);

        printf("%-8d %-15lld %-15lld %-15lld %-15lld\n", n, a1, a2, a3, a4);
    }

    return 0;
}

