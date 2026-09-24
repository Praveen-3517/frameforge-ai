/**
 * Problem: Divide Two Integers (LeetCode 29)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given two integers dividend and divisor, divide them without using multiplication,
 * division, or mod operator. Truncate toward zero. Clamp to 32-bit signed integer range.
 * 
 * Approach - Bit Shift Division:
 * Binary long division: Starting from the highest power of 2 * divisor that fits into dividend,
 * subtract and accumulate quotient bits.
 * 
 * Edge case: dividend = Integer.MIN_VALUE and divisor = -1 overflows to Integer.MAX_VALUE.
 * 
 * Time Complexity: O(log^2 N)
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

int divide(int dividend, int divisor) {
        // Handle overflow edge case
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine sign of result
        bool negative = (dividend < 0) != (divisor < 0);

        // Work with positive long long values to avoid overflow
        long long a = abs((long long) dividend);
        long long b = abs((long long) divisor);
        long long quotient = 0;

        while (a >= b) {
            long long temp = b;
            long long multiple = 1;

            // Find the largest multiple of b that fits into a
            while (a >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }

            a -= temp;
            quotient += multiple;
        }

        return negative ? (int) -quotient : (int) quotient;
    }

    int main(void) {
        printf("10 / 3 = " + divide(10, 3) + " (Expected: 3)\n");
        printf("7 / -3 = " + divide(7, -3) + " (Expected: -2)\n");
        printf("MIN_VALUE / -1 = " + divide(INT_MIN, -1) + " (Expected: 2147483647)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
