/**
 * Problem Statement:
 * Given an integer `n`, compute the sum of the first `n` natural numbers (1 + 2 + ... + n).
 * Prevent 32-bit integer overflow when `n` is large (e.g. n = 100,000).
 *
 * Asked in: Microsoft, Amazon, TCS
 *
 * Approach:
 * - Mathematical formula: S = n * (n + 1) / 2
 * - Pitfall: If n = 100,000, n * (n + 1) = 10,000,100,000 which exceeds Integer.MAX_VALUE (2,147,483,647).
 *   If evaluated purely as 32-bit `int`, it silently overflows into negative numbers.
 * - Solution: Cast `n` to `long` before multiplication: `(long) n * (n + 1) / 2`.
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

// Buggy implementation vulnerable to integer overflow
    int sumBuggy(int n) {
        return (n * (n + 1)) / 2;
    }

    // Correct, overflow-safe implementation using 64-bit promotion
    long long sumSafe(int n) {
        if (n < 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
        return ((long long) n * (n + 1L)) / 2L;
    }

    int main(void) {
        printf("=== Sum of First N Natural Numbers ===\n");

        int* testCases = { 10, 100, 1000, 70000, 100000 };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            long long safeResult = sumSafe(n);
            int buggyResult = sumBuggy(n);

            printf("n = %d\n", n);
            printf("  Safe (long long) result : %d\n", safeResult);
            printf("  Buggy (int) result : %d%d\n", buggyResult, (safeResult != buggyResult ? " <--- OVERFLOW DETECTED!" : ""));
            printf("\n");
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant closed-form formula.
 * Space Complexity: O(1) - Single 64-bit long return.
 */
