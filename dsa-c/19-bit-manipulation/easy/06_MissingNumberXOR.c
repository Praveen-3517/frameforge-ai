/**
 * Problem: Missing Number (LeetCode 268)
 * Asked in: Microsoft, Amazon, Google, Apple, Bloomberg
 * 
 * Given an array nums containing n distinct numbers in the range [0, n],
 * return the only number in the range that is missing from the array.
 * 
 * Approach - XOR:
 * XOR all indices from 0 to n, then XOR all array values.
 * Every index that appears in both cancels out via XOR (x ^ x = 0).
 * The missing number remains as only one index has no matching value.
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

int missingNumber(int* nums) {
        int xor = n; // XOR with n first
        for (int i = 0; i < n; i++) {
            xor ^= i;
            xor ^= nums[i];
        }
        return xor;
    }

    int main(void) {
        int* nums1 = {3, 0, 1};
        printf("Missing from [3,0,1]: " + missingNumber(nums1) + " (Expected: 2)\n");

        int* nums2 = {0, 1};
        printf("Missing from [0,1]: " + missingNumber(nums2) + " (Expected: 2)\n");

        int* nums3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
        printf("Missing from [9..0]: " + missingNumber(nums3) + " (Expected: 8)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
