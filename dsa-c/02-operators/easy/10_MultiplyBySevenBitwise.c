/**
 * Problem Statement:
 * Multiply a given integer `n` by 7 without using the multiplication (*) operator.
 * Extend this pattern to demonstrate how compilers optimize constant multiplications
 * using shift-and-add / shift-and-subtract sequences.
 *
 * Example:
 * n = 4  -> 28
 * n = -3 -> -21
 *
 * Asked in: Adobe, Qualcomm, Samsung, TCS
 *
 * Approach:
 * - Mathematical Decomposition:
 *   7 * n = (8 - 1) * n = (8 * n) - n
 * - Bitwise Left Shift:
 *   Multiplying by powers of two is equivalent to left shifting: 8 * n == (n << 3).
 *   Therefore: `(n << 3) - n`.
 * - Precedence Gotcha:
 *   Bitwise shifts `<<` have lower precedence than subtraction `-`!
 *   Writing `n << 3 - n` evaluates as `n << (3 - n)`, leading to catastrophic bugs!
 *   Always enclose shift operations in parentheses: `((n << 3) - n)`.
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

int multiplyBy7(int n) {
        // Correct parentheses to prevent precedence bug: << has lower precedence than -
        return (n << 3) - n;
    }

    int multiplyBy9(int n) {
        // 9 * n = 8 * n + n
        return (n << 3) + n;
    }

    int multiplyBy15(int n) {
        // 15 * n = 16 * n - n
        return (n << 4) - n;
    }

    int main(void) {
        printf("=== Multiply by 7 (and other constants) Without '*' Operator ===\n");

        int* testCases = { 0, 1, 4, -3, 10, -12, 1000 };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            int by7 = multiplyBy7(n);
            int by9 = multiplyBy9(n);
            int by15 = multiplyBy15(n);
            printf("n = %5d ==> *7: %6d | *9: %6d | *15: %6d (Verified: %s)\n",
                    n, by7, by9, by15, (by7 == n * 7) ? "OK" : "ERROR");
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Bitwise shift and subtraction run in 1 CPU cycle.
 * Space Complexity: O(1) - Constant stack registers.
 */
