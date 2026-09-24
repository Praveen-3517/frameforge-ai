/**
 * Problem: House Robber (LeetCode 198)
 * Asked in: Amazon, Google, Microsoft, Facebook, Apple
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a
 * certain amount of money stashed. Adjacent houses have security systems connected that
 * will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the
 * maximum amount of money you can rob tonight without alerting the police.
 * 
 * Approach:
 * Linear 1D DP:
 * At house i:
 * - Option 1: Rob house i -> profit = nums[i] + rob(i - 2)
 * - Option 2: Skip house i -> profit = rob(i - 1)
 * dp[i] = max(dp[i - 1], nums[i] + dp[i - 2])
 * Space optimized to O(1) using two variables.
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

int rob(int* nums) {
        if (nums == NULL || n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = 0;
        int prev1 = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            int curr = MAX(prev1, num + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int main(void) {
        int* nums1 = {1, 2, 3, 1};
        printf("Max loot 1: " + rob(nums1) + " (Expected: 4)\n");

        int* nums2 = {2, 7, 9, 3, 1};
        printf("Max loot 2: " + rob(nums2) + " (Expected: 12)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
