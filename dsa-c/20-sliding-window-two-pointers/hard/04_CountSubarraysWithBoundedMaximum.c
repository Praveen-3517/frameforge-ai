/**
 * Problem: Count Subarrays with Bounded Maximum (LeetCode 795)
 * Category: Two Pointers | Hard
 * Asked in: Amazon, Google
 * 
 * Given an integer array nums and two integers left and right, return the number of
 * contiguous non-empty subarrays such that the value of the maximum array element in
 * that subarray is in the range [left, right].
 * 
 * Approach - Count(max <= right) - Count(max <= left-1):
 * Helper function countAtMost(bound): counts subarrays where max <= bound.
 * For each i, dp = (i - start) = number of subarrays ending at i with max <= bound.
 * If nums[i] > bound: reset start = i + 1, dp = 0.
 * 
 * Answer = countAtMost(right) - countAtMost(left - 1)
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

static long long countAtMost(int* nums, int bound) {
        long long count = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] > bound) {
                start = i + 1; // reset window
            }
            count += i - start + 1;
        }

        return count;
    }

    int numSubarrayBoundedMax(int* nums, int left, int right) {
        return (int) (countAtMost(nums, right) - countAtMost(nums, left - 1));
    }

    int main(void) {
        printf("%d (Expected: 3)\n", numSubarrayBoundedMax((int[]){2, 1, 4, 3}, 2, 3));
        // [2], [2,1], [3] — three subarrays with max in [2,3]
        printf("%d (Expected: 7)\n", numSubarrayBoundedMax((int[]){2, 9, 2, 5, 6}, 2, 8));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
