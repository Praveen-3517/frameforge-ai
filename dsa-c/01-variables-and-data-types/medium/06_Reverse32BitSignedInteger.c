/**
 * Problem Statement:
 * Given a signed 32-bit integer `x`, return `x` with its digits reversed.
 * If reversing `x` causes the value to go outside the signed 32-bit integer range
 * [-2^31, 2^31 - 1], then return 0.
 * Assume the environment does not allow storing 64-bit integers (`long` is prohibited in solution).
 * (LeetCode 7: Reverse Integer).
 *
 * Asked in: Amazon, Apple, Bloomberg, Microsoft
 *
 * Approach:
 * - Pop digits one by one: `pop = x % 10; x /= 10;`
 * - Before pushing `rev = rev * 10 + pop`, check if doing so will overflow:
 *     1. If `rev > Integer.MAX_VALUE / 10` or (`rev == Integer.MAX_VALUE / 10 && pop > 7`) -> return 0.
 *     2. If `rev < Integer.MIN_VALUE / 10` or (`rev == Integer.MIN_VALUE / 10 && pop < -8`) -> return 0.
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

int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;

            // Check for positive overflow
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) {
                return 0;
            }
            // Check for negative underflow
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) {
                return 0;
            }

            rev = rev * 10 + pop;
        }
        return rev;
    }

    int main(void) {
        int* testCases = {
            123,
            -123,
            120,
            0,
            1534236469, // Reversing this exceeds INT_MAX -> returns 0
            -2147483412,
            INT_MAX
        };

        printf("=== LeetCode 7: Reverse 32-bit int ===\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int x = testCases[_idx];
            int reversed = reverse(x);
            printf("Input: %-12d ==> Output: %-12d\n", x, reversed);
        }
        return 0;
}

/*
 * Time Complexity: O(log10 |x|) - Loop runs at most 10 times for 32-bit integer.
 * Space Complexity: O(1) - Constant stack space with zero 64-bit long promotion.
 */
