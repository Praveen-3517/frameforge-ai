/**
 * Problem: Fibonacci Number (LeetCode 509)
 * Asked in: Amazon, Microsoft, Apple
 * 
 * F(0) = 0, F(1) = 1
 * F(n) = F(n - 1) + F(n - 2), for n > 1.
 * Given n, calculate F(n).
 * 
 * Approach:
 * Iterative dynamic programming with O(1) space:
 * Maintain only the last two Fibonacci numbers.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int fib(int n) {
        if (n <= 1) return n;

        int a = 0;
        int b = 1;

        for (int i = 2; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }

        return b;
    }

    int main(void) {
        printf("F(2): " + fib(2) + " (Expected: 1)\n");
        printf("F(3): " + fib(3) + " (Expected: 2)\n");
        printf("F(4): " + fib(4) + " (Expected: 3)\n");
        printf("F(10): " + fib(10) + " (Expected: 55)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
