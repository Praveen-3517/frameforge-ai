/**
 * Problem Statement:
 * Given an integer array `nums`, find the subarray with the largest sum, and return its sum.
 * Also return the start and end indices of that maximum subarray.
 * (LeetCode 53: Maximum Subarray).
 *
 * Example:
 * nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * The contiguous subarray [4, -1, 2, 1] has the largest sum = 6.
 *
 * Asked in: Amazon, Microsoft, Google, Apple, Bloomberg
 *
 * Approach:
 * - Kadane's Algorithm (O(N) Time, O(1) Space):
 *   At each element `nums[i]`, we decide whether to:
 *   1. Extend the existing running subarray sum: `currentSum + nums[i]`
 *   2. Start a fresh new subarray starting at `nums[i]`: `nums[i]`
 *   Recurrence: `currentSum = Math.max(nums[i], currentSum + nums[i])`.
 *   Global max: `maxSum = Math.max(maxSum, currentSum)`.
 * - Tracking Subarray Indices:
 *   If `currentSum` resets to `nums[i]`, reset `tempStart = i`.
 *   Whenever `maxSum` updates to a new high, set `start = tempStart` and `end = i`.
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
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < n; i++) {
            currentSum = MAX(nums[i], currentSum + nums[i]);
            maxSum = MAX(maxSum, currentSum);
        }

        return maxSum;
    }

    int* maxSubArrayWithIndices(int* nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];
        int start = 0, end = 0, tempStart = 0;

        for (int i = 1; i < n; i++) {
            if (nums[i] > currentSum + nums[i]) {
                currentSum = nums[i];
                tempStart = i;
            } else {
                currentSum += nums[i];
            }

            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }
        }

        return (int[]){ maxSum, start, end };
    }

    int main(void) {
        printf("=== LeetCode 53: Kadane's Algorithm (Maximum Subarray Sum) ===\n");

        int** testCases = {
            { -2, 1, -3, 4, -1, 2, 1, -5, 4 }, // Expected: 6 [indices 3..6]
            { 1 },
            { 5, 4, -1, 7, 8 },                 // Expected: 23
            { -5, -2, -8, -1 }                  // All negative: returns max single element -1
        };

        for (int* arr : testCases) {
            int* info = maxSubArrayWithIndices(arr);
            printf("Array: %s\n ==> Max Sum: %d (From index %d to %d)\n\n",
                    java.util."[array]", info[0], info[1], info[2]);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(1) - Constant stack registers.
 */
