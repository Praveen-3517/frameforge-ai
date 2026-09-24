/**
 * Problem Statement:
 * Given two integers `dividend` and `divisor`, divide two integers without using
 * multiplication, division, and mod operator.
 * Return the quotient after dividing dividend by divisor.
 * Integer division should truncate toward zero.
 * Assume 32-bit signed integers; handle overflow when `dividend = -2147483648` and `divisor = -1`
 * (should clamp to `Integer.MAX_VALUE`).
 * (LeetCode 29: Divide Two Integers).
 *
 * Asked in: Facebook, Amazon, Google, Microsoft
 *
 * Approach:
 * - Exponential Bit Shifting (Bitwise Long Division):
 *   Instead of linear subtraction (which TLEs for 2^31 / 1), subtract largest multiples
 *   of divisor shifted by powers of two: `(divisor << shift)`.
 * - To prevent 32-bit overflow during negation of `Integer.MIN_VALUE`, convert both numbers
 *   to `long` or work entirely with negative numbers in two's complement.
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
        // Corner Case: Overflow on INT_MIN / -1
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine sign of quotient
        bool isNegative = (dividend < 0) ^ (divisor < 0);

        // Convert to long long to avoid abs(INT_MIN) overflow
        long long dvd = abs((long long) dividend);
        long long dvs = abs((long long) divisor);

        int quotient = 0;

        // Exponential bit shift subtraction
        while (dvd >= dvs) {
            long long tempDivisor = dvs;
            int multiple = 1;

            // double the divisor as long long as it fits inside dvd
            while (dvd >= (tempDivisor << 1)) {
                tempDivisor <<= 1;
                multiple <<= 1;
            }

            dvd -= tempDivisor;
            quotient += multiple;
        }

        return isNegative ? -quotient : quotient;
    }

    int main(void) {
        printf("=== LeetCode 29: Divide Two Integers (Bit Shifts) ===\n");

        int** testCases = {
            { 10, 3 },
            { 7, -3 },
            { 0, 1 },
            { -1, 1 },
            { INT_MIN, -1 },  // Overflow edge case
            { INT_MIN, 1 },
            { INT_MIN, 2 },
            { 2147483647, 2 }
        };

        for (int* tc : testCases) {
            int dividend = tc[0];
            int divisor = tc[1];
            int result = divide(dividend, divisor);
            printf("Divide(%d, %d) ==> Quotient: %d\n", dividend, divisor, result);
        }
        return 0;
}

/*
 * Time Complexity: O(log^2 N) - In each step we find the largest power of two multiple in O(log N).
 * Space Complexity: O(1) - Primitive register variables only.
 */
