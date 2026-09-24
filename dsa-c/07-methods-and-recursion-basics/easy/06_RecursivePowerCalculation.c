/**
 * Problem Statement:
 * Compute `x^n` (x raised to the power n) using recursion.
 * Compare two implementations:
 * 1. Naive Linear Recursion: `O(N)` time and call stack depth.
 * 2. Logarithmic Divide-and-Conquer Exponentiation: `O(log N)` time and call stack depth.
 *
 * Asked in: Amazon, Microsoft, TCS, Infosys
 *
 * Approach:
 * - Method 1: Linear Recursion (O(N)):
 *   `power(x, n) = x * power(x, n - 1)` with base case `n == 0 -> 1`.
 * - Method 2: Divide & Conquer (O(log N)):
 *   - If n is even: `x^n = (x^(n/2))^2`
 *   - If n is odd : `x^n = x * (x^(n/2))^2`
 *   Evaluating `half = power(x, n / 2)` once and squaring halves the problem size at each step!
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

// Linear Recursion: O(N)
    long long powerLinear(long long x, int n) {
        if (n == 0) return 1L;
        return x * powerLinear(x, n - 1);
    }

    // Divide and Conquer: O(log N)
    long long powerDivideAndConquer(long long x, int n) {
        if (n == 0) return 1L;

        long long half = powerDivideAndConquer(x, n / 2);

        if ((n & 1) == 0) {
            return half * half;
        } else {
            return x * half * half;
        }
    }

    int main(void) {
        printf("=== Recursive Power Calculation: O(N) vs O(log N) ===\n");

        long long x = 2;
        int n = 30;

        long long ansLinear = powerLinear(x, n);
        long long ansLog = powerDivideAndConquer(x, n);

        printf("%d^%d via Linear Recursion (O(N))       : %d\n", x, n, ansLinear);
        printf("%d^%d via Divide & Conquer (O(log N)) : %d\n", x, n, ansLog);
        return 0;
}

/*
 * Time Complexity:
 *   - Linear: O(N)
 *   - Divide & Conquer: O(log N)
 * Space Complexity:
 *   - Linear: O(N) call stack frames
 *   - Divide & Conquer: O(log N) call stack frames
 */
