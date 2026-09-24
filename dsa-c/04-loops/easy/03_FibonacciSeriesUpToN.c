/**
 * Problem Statement:
 * Generate the first N numbers of the Fibonacci sequence:
 *   F(0) = 0, F(1) = 1, F(n) = F(n - 1) + F(n - 2) for n >= 2.
 * Implement an iterative solution using constant auxiliary space O(1).
 * Handle large values of N safely using 64-bit `long` (since F(47) overflows signed 32-bit `int`).
 *
 * Asked in: TCS, Infosys, Amazon, Accenture, Wipro
 *
 * Approach:
 * - Space-Optimized Iterative Loop:
 *   Instead of allocating an array of size N (which costs O(N) heap memory),
 *   maintain only two variables: `prev2 = 0` and `prev1 = 1`.
 *   In each iteration of the loop:
 *     `long current = prev1 + prev2;`
 *     `prev2 = prev1;`
 *     `prev1 = current;`
 * - Time: O(N), Space: O(1).
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

long long* generateFibonacci(int n) {
        if (n <= 0) return (long long*)malloc((0) * sizeof(long long));
        if (n == 1) return new long long[] { 0L };

        long long* fib = (long long*)malloc((n) * sizeof(long long));
        fib[0] = 0L;
        fib[1] = 1L;

        for (int i = 2; i < n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        return fib;
    }

    long long getNthFibonacciSpaceOptimized(int n) {
        if (n <= 0) return 0L;
        if (n == 1) return 1L;

        long long prev2 = 0L;
        long long prev1 = 1L;

        for (int i = 2; i <= n; i++) {
            long long curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int main(void) {
        printf("=== Iterative Fibonacci Series (O(1) Space) ===\n");

        int n = 15;
        long long* sequence = generateFibonacci(n);
        printf("First %d Fibonacci Numbers:\n", n);
        for (int i = 0; i < n; i++) {
            printf("F(%2d) = %4d\n", i, sequence[i]);
        }

        printf("\nLarge Fibonacci Calculation (64-Bit Safe):\n");
        int* queryTerms = { 20, 30, 45, 50 };
        for (size_t _idx = 0; _idx < sizeof(queryTerms)/sizeof(queryTerms[0]); _idx++) {
        int q = queryTerms[_idx];
            printf("F(%2d) = %d\n", q, getNthFibonacciSpaceOptimized(q));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single loop of N iterations.
 * Space Complexity: O(1) - Two local register variables.
 */
