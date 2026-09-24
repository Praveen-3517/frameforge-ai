/**
 * Problem: Partition Equal Subset Sum (LeetCode 416)
 * Asked in: Facebook, Amazon, Microsoft, Uber
 * 
 * Given an integer array nums, return true if you can partition the array into two subsets
 * such that the sum of the elements in both subsets is equal or false otherwise.
 * 
 * Approach:
 * 0/1 Knapsack / Subset Sum DP:
 * 1. Compute total sum S. If S is odd, return false (cannot partition into two equal integers).
 * 2. Target sum T = S / 2.
 * 3. Use 1D boolean array dp of size T + 1:
 *    - dp[0] = true (0 sum is always achievable).
 *    - For each num in nums:
 *      - Iterate backwards j from T down to num:
 *        dp[j] = dp[j] || dp[j - num]
 * 4. Return dp[T].
 * 
 * Time Complexity: O(N * Target) = O(N * S / 2)
 * Space Complexity: O(Target) = O(S / 2)
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

bool canPartition(int* nums) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;

        if (totalSum % 2 != 0) return false;

        int target = totalSum / 2;
        bool[] dp = (bool*)malloc((target + 1) * sizeof(bool));
        dp[0] = true;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }

    int main(void) {
        int* nums1 = {1, 5, 11, 5};
        printf("Can partition [1, 5, 11, 5]: " + canPartition(nums1) + " (Expected: true)\n");

        int* nums2 = {1, 2, 3, 5};
        printf("Can partition [1, 2, 3, 5]: " + canPartition(nums2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
