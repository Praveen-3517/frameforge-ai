/**
 * Problem Statement:
 * Given two integers `left` and `right` that represent the range `[left, right]`,
 * return the bitwise AND of all numbers in this range, inclusive.
 * (0 <= left <= right <= 2^31 - 1).
 * Naive loop iteration causes Time Limit Exceeded (TLE) when the range spans billions of numbers.
 * (LeetCode 201: Bitwise AND of Numbers Range).
 *
 * Asked in: Google, Amazon, Adobe, Microsoft
 *
 * Approach:
 * - Common Prefix Observation:
 *   As numbers increment from `left` to `right`, the least significant bits flip repeatedly
 *   between 0 and 1. If any bit flips to 0 anywhere in the interval, its bitwise AND across
 *   the entire range becomes 0!
 *   Therefore, the problem reduces to finding the Common Binary Prefix of `left` and `right`.
 * - Method 1 (Shift):
 *   Right-shift both `left` and `right` until they become equal, counting the number of shifts.
 *   Then left-shift back by the same count: `left << shifts`.
 * - Method 2 (Brian Kernighan's / Turn Off Lowest Set Bit):
 *   Repeatedly clear the lowest set bit of `right` using `right & (right - 1)` until `right <= left`.
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

// Approach 1: Bit Shift to Find Common Prefix (O(log(right)) time, O(1) space)
    int rangeBitwiseAndShift(int left, int right) {
        int shiftCount = 0;
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shiftCount++;
        }
        return left << shiftCount;
    }

    // Approach 2: Brian Kernighan's Bit Clearing (O(number of 1s in right) time, O(1) space)
    int rangeBitwiseAndBK(int left, int right) {
        while (right > left) {
            right = right & (right - 1);
        }
        return right;
    }

    int main(void) {
        printf("=== LeetCode 201: Bitwise AND of Numbers Range ===\n");

        int** testCases = {
            { 5, 7 },              // 5: 101, 6: 110, 7: 111 -> 100 (4)
            { 0, 0 },
            { 1, 2147483647 },     // Massive range: returns 0 instantly
            { 9, 12 },
            { 600000000, 600000005 }
        };

        for (int* tc : testCases) {
            int left = tc[0];
            int right = tc[1];
            int ans1 = rangeBitwiseAndShift(left, right);
            int ans2 = rangeBitwiseAndBK(left, right);
            printf("Range [%d, %d] ==> Shift: %d | BK: %d\n", left, right, ans1, ans2);
        }
        return 0;
}

/*
 * Time Complexity: O(log(MAX_VAL)) = O(32) ≈ O(1) - Number of bits shifted or cleared is at most 32.
 * Space Complexity: O(1) - No heap allocations, uses registers only.
 */
