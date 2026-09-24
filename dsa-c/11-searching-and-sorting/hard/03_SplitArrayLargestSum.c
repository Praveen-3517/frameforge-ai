/*
 * Problem Statement:
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays
 * such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.
 * (LeetCode 410: Split Array Largest Sum)
 * 
 * Example:
 * Input: nums = [7,2,5,10,8], k = 2
 * Output: 18 (Subarrays: [7,2,5] (sum 14) and [10,8] (sum 18); largest sum is 18)
 * 
 * Asked in: Google, Amazon, Facebook/Meta, ByteDance
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

/**
     * Approach:
     * Binary Search on Answer:
     * - Lower bound (low): max element in nums (a subarray of size 1 cannot be smaller than max(nums)).
     * - Upper bound (high): sum of all elements in nums (single subarray containing all elements).
     * - Monotonic test: canSplit(maxAllowedSum, k):
     *   Greedily accumulate elements into a subarray. When sum exceeds maxAllowedSum,
     *   start a new subarray. If total subarrays needed <= k, the bound is feasible.
     */
    int splitArray(int* nums, int k) {
        int low = 0;
        int high = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            low = MAX(low, num);
            high += num;
        }

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canSplit(nums, k, mid)) {
                high = mid; // Try smaller max sum
            } else {
                low = mid + 1; // Need larger capacity
            }
        }

        return low;
    }

    static bool canSplit(int* nums, int k, int maxAllowedSum) {
        int subarrays = 1;
        int currentSum = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if (currentSum + num > maxAllowedSum) {
                subarrays++;
                currentSum = num;
                if (subarrays > k) return false;
            } else {
                currentSum += num;
            }
        }

        return true;
    }

    int main(void) {
        int* nums = {7, 2, 5, 10, 8};
        int k = 2;

        printf("Array: [7, 2, 5, 10, 8], k = 2\n");
        printf("Minimized largest sum: %d\n", splitArray(nums, k));

        int* nums2 = {1, 2, 3, 4, 5};
        int k2 = 2;
        printf("\nArray: [1, 2, 3, 4, 5], k = 2\n");
        printf("Minimized largest sum: %d\n", splitArray(nums2, k2));
        return 0;
}

/*
 * Time Complexity: O(N * log(sum(nums) - max(nums)))
 * Space Complexity: O(1) auxiliary space.
 */
