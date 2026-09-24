/**
 * Problem Statement:
 * Given an integer array `nums` where every element appears three times except for one,
 * which appears exactly once. Find the single element and return it.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 * (LeetCode 137: Single Number II).
 *
 * Asked in: Google, Amazon, Bloomberg, Apple
 *
 * Approach:
 * - Digital Logic / Bit State Machine:
 *   Every bit position can appear 0, 1, 2, or 3 times. We can model a modulo-3 counter using two
 *   variables: `ones` and `twos`.
 *   - `ones` tracks bits that have appeared 1 time (mod 3).
 *   - `twos` tracks bits that have appeared 2 times (mod 3).
 *   - When a bit appears the 3rd time, both `ones` and `twos` reset that bit to 0.
 *   Transition logic:
 *   `ones = (ones ^ num) & ~twos;`
 *   `twos = (twos ^ num) & ~ones;`
 *   After processing all numbers, `ones` holds the bits of the element appearing once.
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

// Approach 1: Bit State Machine (Optimal O(N) time, O(1) space)
    int singleNumberStateCounter(int* nums) {
        int ones = 0;
        int twos = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }

        return ones;
    }

    // Approach 2: 32-Bit Sum Modulo 3 (More intuitive O(32 * N) time, O(1) space)
    int singleNumberBitSum(int* nums) {
        int result = 0;

        for (int i = 0; i < 32; i++) {
            int bitSum = 0;
            for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
                if (((num >> i) & 1) == 1) {
                    bitSum++;
                }
            }
            if (bitSum % 3 != 0) {
                result |= (1 << i);
            }
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 137: Single Number II (Elements Appear 3 Times) ===\n");

        int** testCases = {
            { 2, 2, 3, 2 },
            { 0, 1, 0, 1, 0, 1, 99 },
            { -2, -2, 1, 1, 4, 1, 4, 4, -4, -2 },
            { -19, -46, -19, -46, -9, -9, -19, -46, -9, 42 }
        };

        for (int* nums : testCases) {
            int ans1 = singleNumberStateCounter(nums);
            int ans2 = singleNumberBitSum(nums);
            printf("Array: %s\n -> State Machine: %d | Bit-Sum: %d\n\n",
                    java.util."[array]", ans1, ans2);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single linear pass through the array.
 * Space Complexity: O(1) - Constant auxiliary storage (two 32-bit registers).
 */
