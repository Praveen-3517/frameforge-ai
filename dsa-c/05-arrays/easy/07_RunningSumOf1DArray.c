/**
 * Problem Statement:
 * Given an array `nums`. We define a running sum of an array as:
 *   `runningSum[i] = sum(nums[0] ... nums[i])`.
 * Return the running sum of `nums`.
 * Additionally demonstrate how a Prefix Sum array enables O(1) static Range Sum Queries.
 * (LeetCode 1480: Running Sum of 1d Array).
 *
 * Example:
 * [1, 2, 3, 4] -> [1, 3, 6, 10]
 *
 * Asked in: Amazon, Apple, Google, Adobe
 *
 * Approach:
 * - Prefix Sum Recurrence:
 *   `runningSum[i] = runningSum[i - 1] + nums[i]` for i >= 1.
 * - Range Sum Query Application:
 *   Sum of subarray nums[L..R] is computed in O(1) time:
 *   `sum(L, R) = prefix[R] - (L > 0 ? prefix[L - 1] : 0)`.
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

// Return new array with prefix sum
    int* runningSum(int* nums) {
        if (nums == NULL || n == 0) return (int*)malloc((0) * sizeof(int));

        int* prefix = (int*)malloc((n) * sizeof(int));
        prefix[0] = nums[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }

        return prefix;
    }

    // O(1) Range Sum Query helper
    int rangeSumQuery(int* prefix, int left, int right) {
        if (left == 0) return prefix[right];
        return prefix[right] - prefix[left - 1];
    }

    int main(void) {
        printf("=== LeetCode 1480: Running Sum (Prefix Sum & O(1) Range Query) ===\n");

        int* nums = { 3, 1, 2, 10, 1 };
        int* prefix = runningSum(nums);

        printf("Original Array : " + "[array]\n");
        printf("Running Sum    : " + "[array]\n");

        // Range query tests
        printf("\nRange Sum Queries in O(1) time:\n");
        printf("Sum of range [1..3] (indices 1 to 3: 1+2+10) = %d\n", rangeSumQuery(prefix, 1, 3));
        printf("Sum of range [0..4] (entire array sum)       = %d\n", rangeSumQuery(prefix, 0, 4));
        return 0;
}

/*
 * Time Complexity:
 *   - Precomputation: O(N)
 *   - Range query: O(1)
 * Space Complexity: O(N) - Storage for the prefix sum array.
 */
