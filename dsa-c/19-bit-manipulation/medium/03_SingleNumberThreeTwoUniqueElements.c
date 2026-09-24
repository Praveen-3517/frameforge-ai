/**
 * Problem: Single Number III (LeetCode 260)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an integer array nums, in which exactly two elements appear only once
 * and all other elements appear exactly twice, find the two elements that appear once.
 * You must use O(1) extra space.
 * 
 * Approach - XOR with Bit Separator:
 * 1. XOR all numbers: xorAll = a ^ b (where a, b are the two unique elements).
 * 2. Find any set bit in xorAll (use xorAll & (-xorAll) to isolate rightmost set bit = diffBit).
 *    This bit differs between a and b.
 * 3. Partition array into two groups based on diffBit:
 *    - Group 1: numbers where diffBit is set.
 *    - Group 2: numbers where diffBit is clear.
 * 4. XOR each group independently: pairs cancel, leaving a and b.
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

int* singleNumber(int* nums) {
        int xorAll = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            xorAll ^= num;
        }

        // Isolate the rightmost differing bit
        int diffBit = xorAll & (-xorAll);

        int a = 0;
        int b = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if ((num & diffBit) != 0) {
                a ^= num;
            } else {
                b ^= num;
            }
        }

        return (int[]){a, b};
    }

    int main(void) {
        int* nums1 = {1, 2, 1, 3, 2, 5};
        printf("Two unique: %d\n", "[array]"));
        // Expected: [3, 5] (order may vary)

        int* nums2 = {-1, 0};
        printf("Two unique: %d\n", "[array]"));
        // Expected: [-1, 0]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
