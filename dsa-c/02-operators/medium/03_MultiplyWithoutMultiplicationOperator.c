/**
 * Problem Statement:
 * Multiply two integers `a` and `b` without using the multiplication operator (*).
 * Handle positive, negative, and zero inputs efficiently in O(log b) time.
 *
 * Asked in: Amazon, Cisco, Goldman Sachs, Intel
 *
 * Approach:
 * - Russian Peasant / Binary Shift-and-Add Algorithm:
 *   Every integer `b` can be decomposed into a sum of powers of 2 (its binary representation).
 *   For example: 13 * 11:
 *   11 in binary is 1011_2 = (8 + 2 + 1).
 *   13 * 11 = 13 * (8 + 2 + 1) = (13 * 8) + (13 * 2) + (13 * 1).
 *   Multiplying by powers of 2 is achieved by left-shifting `a`: `a <<= 1`.
 *   Checking binary bits of `b` is achieved by `(b & 1)` and right-shifting `b >>>= 1`.
 * - Time complexity is O(32) ≈ O(1) compared to naive linear addition O(b) which TLEs.
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

long long multiply(long long a, long long b) {
        // Determine sign
        bool isNegative = (a < 0) ^ (b < 0);

        long long x = abs(a);
        long long y = abs(b);
        long long result = 0;

        while (y > 0) {
            // If the lowest bit of y is 1, add current x to result
            if ((y & 1) == 1) {
                result += x;
            }

            // double x and halve y
            x <<= 1;
            y >>= 1;
        }

        return isNegative ? -result : result;
    }

    int main(void) {
        printf("=== Russian Peasant Multiplication (Shift-and-Add) ===\n");

        long long** testCases = {
            { 13, 11 },
            { -6, 7 },
            { 14, -5 },
            { -12, -12 },
            { 0, 500 },
            { 123456, 789 },
            { 1000000, 1000000 }
        };

        for (long long* tc : testCases) {
            long long a = tc[0];
            long long b = tc[1];
            long long prod = multiply(a, b);
            printf("%10d * %10d ==> Result: %15d (Expected: %15d)\n",
                    a, b, prod, a * b);
        }
        return 0;
}

/*
 * Time Complexity: O(log |b|) <= O(64) for long - Number of bits in operand b.
 * Space Complexity: O(1) - Constant stack space.
 */
