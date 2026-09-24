/**
 * Problem: Single Number (LeetCode 136)
 * Asked in: Amazon, Google, Microsoft, Apple, Bloomberg
 * 
 * Given a non-empty array of integers nums, every element appears twice except for one.
 * Find that single one. You must implement a solution with linear runtime complexity
 * and use only constant extra space.
 * 
 * Approach:
 * XOR Cancellation:
 * x ^ x = 0
 * x ^ 0 = x
 * XOR is associative and commutative. XORing all numbers cancels duplicate pairs,
 * leaving only the unique element.
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

int singleNumber(int* nums) {
        int single = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            single ^= num;
        }
        return single;
    }

    int main(void) {
        int* nums1 = {2, 2, 1};
        printf("Single number 1: " + singleNumber(nums1) + " (Expected: 1)\n");

        int* nums2 = {4, 1, 2, 1, 2};
        printf("Single number 2: " + singleNumber(nums2) + " (Expected: 4)\n");

        int* nums3 = {1};
        printf("Single number 3: " + singleNumber(nums3) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
