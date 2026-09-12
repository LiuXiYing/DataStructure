#include <stdio.h>

// 算法1：单层循环 O(n)
long long algorithm1(int n){
    long long count = 0;
    for(int i = 0; i < n; i++){
        count++;
    }
    return count;
}

// 算法2：双重循环 O(n^2)
long long algorithm2(int n){
    long long count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){  // 内层次数随外层变化
            count++;
        }
    }
    return count;
}

// 算法3：倍增循环 O(logn)
long long algorithm3(int n){
    long long count = 0;
    int i = 1;
    while(i < n){
        i *= 2;
        count++;
    }
    return count;
}

// 算法4：分治递归 O(logn)
long long algorithm4(int n){
    long long count = 0;
    if(n <= 1){
        count++;
        return count;
    }
    count++;
    return count + algorithm4(n / 2);
}

int main(){
    int ns[] = {2048, 4096, 8192, 16384};
    int len = sizeof(ns) / sizeof(ns[0]);

    for(int i = 0; i < len; i++){
        int n = ns[i];
        long long a1 = algorithm1(n);
        long long a2 = algorithm2(n);
        long long a3 = algorithm3(n);
        long long a4 = algorithm4(n);
        printf("n=%d\t%lld\t%lld\t%lld\t%lld\n", n, a1, a2, a3, a4);
    }
    return 0;
}