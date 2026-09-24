/**
 * Problem: Longest Increasing Subsequence (LeetCode 300)
 * Asked in: Google, Amazon, Microsoft, Apple, Bloomberg
 * 
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * 
 * Approach:
 * Patience Sorting + Binary Search (O(N log N)):
 * Maintain an array `tails` where `tails[i]` stores the smallest tail of all increasing subsequences of length i + 1.
 * For each num in nums:
 * - Use binary search (`Arrays.binarySearch`) to find num's position in `tails`.
 * - If not found, binarySearch returns `-(insertion_point) - 1`.
 * - If insertion_point == size, append num to tails (increasing LIS length by 1).
 * - Otherwise, update `tails[insertion_point] = num` (maintaining smaller possible tail).
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for tails array.
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

int lengthOfLIS(int* nums) {
        int* tails = (int*)malloc((n) * sizeof(int));
        int size = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int x = nums[_idx];
            int i = Arrays.binarySearch(tails, 0, size, x);
            if (i < 0) {
                i = -(i + 1);
            }
            tails[i] = x;
            if (i == size) {
                size++;
            }
        }

        return size;
    }

    int main(void) {
        int* nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
        printf("LIS length 1: " + lengthOfLIS(nums1) + " (Expected: 4)\n");

        int* nums2 = {0, 1, 0, 3, 2, 3};
        printf("LIS length 2: " + lengthOfLIS(nums2) + " (Expected: 4)\n");

        int* nums3 = {7, 7, 7, 7, 7, 7, 7};
        printf("LIS length 3: " + lengthOfLIS(nums3) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
