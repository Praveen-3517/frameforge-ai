/**
 * Problem Statement:
 * Given an integer array `nums`, in which exactly two elements appear only once
 * and all the other elements appear exactly twice. Find the two elements that appear only once.
 * Your algorithm must run in linear runtime O(n) and use only constant extra space O(1).
 * (LeetCode 260: Single Number III).
 *
 * Asked in: Google, Amazon, Microsoft, Directi
 *
 * Approach:
 * 1. XOR all numbers in the array. Since `x ^ x = 0`, all duplicate pairs cancel out.
 *    The final result is `xorSum = a ^ b`, where `a` and `b` are the two unique elements.
 * 2. Since `a != b`, `xorSum != 0`, which means there is at least one set bit where `a` and `b` differ.
 * 3. Find the lowest set bit (rightmost 1-bit) using `diff = xorSum & (-xorSum)`.
 * 4. Partition the entire array into two groups:
 *      Group 1: Numbers that have this bit set (`(num & diff) != 0`)
 *      Group 2: Numbers that have this bit cleared (`(num & diff) == 0`)
 * 5. `a` and `b` will fall into different groups, and duplicates will fall into the same group and cancel out.
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

int* singleNumber(int* nums) {
        // Step 1: XOR all elements to obtain a ^ b
        int xorSum = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            xorSum ^= num;
        }

        // Step 2: Extract rightmost set bit (diff bit)
        // Two's complement trick: x & -x isolates lowest set bit
        int diff = xorSum & (-xorSum);

        // Step 3: Divide into two groups and XOR independently
        int a = 0;
        int b = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if ((num & diff) != 0) {
                a ^= num; // Belongs to group with bit set
            } else {
                b ^= num; // Belongs to group with bit 0
            }
        }

        return (int[]){ a, b };
    }

    int main(void) {
        int* input1 = { 1, 2, 1, 3, 2, 5 };
        int* res1 = singleNumber(input1);
        printf("Input:  " + "[array]\n");
        printf("Output: " + "[array]\n"); // [3, 5] (or [5, 3])

        int* input2 = { -1, 0 };
        int* res2 = singleNumber(input2);
        printf("\nInput:  " + "[array]\n");
        printf("Output: " + "[array]\n");

        int* input3 = { 0, 1 };
        int* res3 = singleNumber(input3);
        printf("\nInput:  " + "[array]\n");
        printf("Output: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Exactly two passes over the array.
 * Space Complexity: O(1) - Constant auxiliary registers without HashSet/HashMap.
 */
