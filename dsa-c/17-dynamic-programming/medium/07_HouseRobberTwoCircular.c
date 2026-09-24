/**
 * Problem: House Robber II (LeetCode 213)
 * Asked in: Amazon, Microsoft, Google
 * 
 * All houses at this place are arranged in a circle. That means the first house is the
 * neighbor of the last one. Meanwhile, adjacent houses have a security system connected,
 * and it will automatically contact the police if two adjacent houses are broken into.
 * Return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Approach:
 * Circular reduction to two linear House Robber subproblems:
 * Since house 0 and house n - 1 cannot both be robbed:
 * - Case 1: Rob houses in range [0, n - 2] (exclude last house).
 * - Case 2: Rob houses in range [1, n - 1] (exclude first house).
 * Answer = max(Case 1, Case 2).
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
        if (n == 2) return MAX(nums[0], nums[1]);

        return MAX(robRange(nums, 0, n - 2),
                        robRange(nums, 1, n - 1));
    }

    static int robRange(int* nums, int start, int end) {
        int prev2 = 0;
        int prev1 = 0;

        for (int i = start; i <= end; i++) {
            int curr = MAX(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int main(void) {
        int* nums1 = {2, 3, 2};
        printf("Max loot 1: " + rob(nums1) + " (Expected: 3)\n");

        int* nums2 = {1, 2, 3, 1};
        printf("Max loot 2: " + rob(nums2) + " (Expected: 4)\n");

        int* nums3 = {1, 2, 3};
        printf("Max loot 3: " + rob(nums3) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
