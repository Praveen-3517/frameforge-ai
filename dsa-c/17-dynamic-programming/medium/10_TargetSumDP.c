/**
 * Problem: Target Sum (LeetCode 494)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-'
 * before each integer in nums and then concatenate all the integers.
 * Return the number of different expressions that you can build, which evaluates to target.
 * 
 * Approach:
 * Mathematical Reduction to Subset Sum (0/1 Knapsack):
 * Let P = subset of positive elements, N = subset of negative elements.
 * P - N = target
 * P + N = totalSum
 * Adding equations: 2P = target + totalSum  =>  P = (target + totalSum) / 2
 * Problem reduces to finding number of subsets with sum P!
 * Constraints: (target + totalSum) must be non-negative and even.
 * 
 * Time Complexity: O(N * P) where P = (target + totalSum) / 2.
 * Space Complexity: O(P) using 1D DP array.
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

int findTargetSumWays(int* nums, int target) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;

        // Valid subset check
        if (abs(target) > totalSum || (target + totalSum) % 2 != 0) {
            return 0;
        }

        int subsetSum = (target + totalSum) / 2;
        int* dp = (int*)malloc((subsetSum + 1) * sizeof(int));
        dp[0] = 1; // One way to make sum 0 (empty subset)

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            for (int j = subsetSum; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }

        return dp[subsetSum];
    }

    int main(void) {
        int* nums1 = {1, 1, 1, 1, 1};
        printf("Ways for target 3: " + findTargetSumWays(nums1, 3) + " (Expected: 5)\n");

        int* nums2 = {1};
        printf("Ways for target 1: " + findTargetSumWays(nums2, 1) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
