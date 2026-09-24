/**
 * Problem Statement:
 * Given an integer array `nums` and an integer `k`, return the number of good subarrays of `nums`.
 * A good array is an array where the number of different integers in that array is EXACTLY `k`.
 * (LeetCode 992: Subarrays with K Different Integers - Hard).
 *
 * Example:
 * nums = [1, 2, 1, 2, 3], k = 2 -> Output: 7
 *
 * Asked in: Google, Amazon, Microsoft, Uber
 *
 * Approach:
 * - Exact K via Difference of "At Most K":
 *   Directly finding subarrays with EXACTLY K distinct elements with sliding window is tricky
 *   because shrinking the window when distinct == K loses other valid sub-windows.
 *   Key Mathematical Reduction:
 *   `countExact(K) = countAtMost(K) - countAtMost(K - 1)`!
 * - Helper `countAtMost(nums, k)` (Sliding Window in O(N)):
 *   - Maintain frequency array `freq` and count of distinct numbers `distinct`.
 *   - Expand `right` pointer:
 *     If `freq[nums[right]]++ == 0`: `distinct++`.
 *   - While `distinct > k`:
 *     If `--freq[nums[left++]] == 0`: `distinct--`.
 *   - The number of subarrays ending at `right` with AT MOST K distinct integers is:
 *     `right - left + 1`.
 *   - Sum over all `right`.
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

int subarraysWithKDistinct(int* nums, int k) {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
    }

    static int atMostKDistinct(int* nums, int k) {
        if (k <= 0) return 0;

        int n = n;
        int* freq = (int*)malloc((n + 1) * sizeof(int));
        int distinct = 0;
        int left = 0;
        int count = 0;

        for (int right = 0; right < n; right++) {
            if (freq[nums[right]]++ == 0) {
                distinct++;
            }

            while (distinct > k) {
                if (--freq[nums[left]] == 0) {
                    distinct--;
                }
                left++;
            }

            count += right - left + 1;
        }

        return count;
    }

    int main(void) {
        printf("=== LeetCode 992: Subarrays with K Different Integers ===\n");

        int* nums1 = { 1, 2, 1, 2, 3 };
        int k1 = 2;
        printf("nums: %s, k = %d ==> Exact K Subarrays: %d (Expected: 7)\n",
                java.util."[array]", k1, subarraysWithKDistinct(nums1, k1));

        int* nums2 = { 1, 2, 1, 3, 4 };
        int k2 = 3;
        printf("nums: %s, k = %d ==> Exact K Subarrays: %d (Expected: 3)\n",
                java.util."[array]", k2, subarraysWithKDistinct(nums2, k2));
        return 0;
}

/*
 * Time Complexity: O(N) - Two passes of sliding window, each element visited twice.
 * Space Complexity: O(N) - Primitive frequency array.
 */
