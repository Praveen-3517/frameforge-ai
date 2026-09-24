/**
 * Problem: Maximum Subarray / Kadane's Algorithm (LeetCode 53)
 * Asked in: Amazon, Microsoft, Apple, Google, Bloomberg
 * 
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 * 
 * Approach:
 * Kadane's Algorithm (1D DP):
 * Let dp[i] be the maximum subarray sum ending at index i.
 * Transition:
 * dp[i] = max(nums[i], nums[i] + dp[i - 1])
 * Either start a fresh subarray at nums[i], or extend the existing previous subarray.
 * Maintain running maximum in O(1) space.
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

int maxSubArray(int* nums) {
        int currentMax = nums[0];
        int globalMax = nums[0];

        for (int i = 1; i < n; i++) {
            currentMax = MAX(nums[i], currentMax + nums[i]);
            globalMax = MAX(globalMax, currentMax);
        }

        return globalMax;
    }

    int main(void) {
        int* nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        printf("Max Subarray 1: " + maxSubArray(nums1) + " (Expected: 6)\n");

        int* nums2 = {1};
        printf("Max Subarray 2: " + maxSubArray(nums2) + " (Expected: 1)\n");

        int* nums3 = {5, 4, -1, 7, 8};
        printf("Max Subarray 3: " + maxSubArray(nums3) + " (Expected: 23)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
