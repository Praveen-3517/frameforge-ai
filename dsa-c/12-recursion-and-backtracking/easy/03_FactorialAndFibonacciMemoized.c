/*
 * Problem Statement:
 * Compare Naive vs Memoized Recursion:
 * - Fibonacci Number (LeetCode 509):
 *   - Naive recursion: O(2^N) time due to overlapping redundant subtrees.
 *   - Top-down memoized recursion: O(N) time with array/HashMap cache.
 * - Factorial calculation with memoization table.
 * 
 * Asked in: TCS, Infosys, Capgemini, Amazon
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

// 1. Fibonacci with Memoization
    long long fibMemo(int n) {
        long long* memo = (long long*)malloc((n + 1) * sizeof(long long));
        return fibHelper(n, memo);
    }

    static long long fibHelper(int n, long long* memo) {
        if (n <= 1) return n;
        if (memo[n] != 0) return memo[n];
        return memo[n] = fibHelper(n - 1, memo) + fibHelper(n - 2, memo);
    }

    // 2. Naive Fibonacci (Exponential O(2^N))
    long long fibNaive(int n) {
        if (n <= 1) return n;
        return fibNaive(n - 1) + fibNaive(n - 2);
    }

    int main(void) {
        printf("--- Fibonacci Comparison ---\n");
        int n = 40;

        long long t1 = System.currentTimeMillis();
        long long resMemo = fibMemo(n);
        long long t2 = System.currentTimeMillis();
        printf("Memoized fib(%d) = %d in %dms\n", n, resMemo, (t2 - t1));

        long long t3 = System.currentTimeMillis();
        long long resNaive = fibNaive(n);
        long long t4 = System.currentTimeMillis();
        printf("Naive    fib(%d) = %d in %dms\n", n, resNaive, (t4 - t3));
        return 0;
}

/*
 * Time Complexity: Memoized: O(N), Naive: O(2^N).
 * Space Complexity: O(N) memoization array and call stack depth.
 */
