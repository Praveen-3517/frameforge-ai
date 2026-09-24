/**
 * Problem Statement:
 * Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively,
 * return the median of the two sorted arrays.
 * The overall run time complexity must be O(log(min(m, n))).
 * (LeetCode 4: Median of Two Sorted Arrays - Hard).
 *
 * Example:
 * nums1 = [1, 3], nums2 = [2] -> Median: 2.0
 * nums1 = [1, 2], nums2 = [3, 4] -> Median: (2 + 3) / 2 = 2.5
 *
 * Asked in: Google, Amazon, Microsoft, Apple, Goldman Sachs
 *
 * Approach:
 * - Binary Search Partitioning on the Shorter Array (O(log(min(m, n)))):
 *   1. Always perform binary search on the shorter array (if `m > n`, swap arrays).
 *   2. We want to partition both arrays into two halves (Left Half and Right Half) such that:
 *      - Total elements on left = `(m + n + 1) / 2`.
 *      - Every element in Left Half <= Every element in Right Half.
 *   3. Partition `partX` in `nums1` and `partY = (m + n + 1) / 2 - partX` in `nums2`:
 *      - `maxLeftX  = (partX == 0) ? -INF : nums1[partX - 1]`
 *      - `minRightX = (partX == m) ? +INF : nums1[partX]`
 *      - `maxLeftY  = (partY == 0) ? -INF : nums2[partY - 1]`
 *      - `minRightY = (partY == n) ? +INF : nums2[partY]`
 *   4. Valid Partition Condition:
 *      `maxLeftX <= minRightY && maxLeftY <= minRightX`
 *      - If total length is odd: `median = Math.max(maxLeftX, maxLeftY)`
 *      - If total length is even: `median = (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0`
 *   5. Adjust Binary Search:
 *      - If `maxLeftX > minRightY`: `high = partX - 1` (too far right in nums1)
 *      - Else: `low = partX + 1` (too far left in nums1)
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

double findMedianSortedArrays(int* nums1, int* nums2) {
        // Guarantee nums1 is the shorter array
        if (n > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = n;
        int n = n;
        int low = 0;
        int high = m;

        while (low <= high) {
            int partX = (low + high) / 2;
            int partY = (m + n + 1) / 2 - partX;

            int maxLeftX = (partX == 0) ? INT_MIN : nums1[partX - 1];
            int minRightX = (partX == m) ? INT_MAX : nums1[partX];

            int maxLeftY = (partY == 0) ? INT_MIN : nums2[partY - 1];
            int minRightY = (partY == n) ? INT_MAX : nums2[partY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // Correct partition reached
                if (((m + n) & 1) == 1) { // Odd total length
                    return MAX(maxLeftX, maxLeftY);
                } else { // Even total length
                    return (MAX(maxLeftX, maxLeftY) + MIN(minRightX, minRightY)) / 2.0;
                }
            } else if (maxLeftX > minRightY) {
                high = partX - 1; // Move left in nums1
            } else {
                low = partX + 1;  // Move right in nums1
            }
        }

        fprintf(stderr, "Exception: invalid argument
"); return 0;
    }

    int main(void) {
        printf("=== LeetCode 4: Median of Two Sorted Arrays (Binary Partition) ===\n");

        int* a1 = { 1, 3 };
        int* b1 = { 2 };
        printf("Arrays: %s and %s ==> Median: %.1f\n",
                java.util."[array]", java.util."[array]", findMedianSortedArrays(a1, b1));

        int* a2 = { 1, 2 };
        int* b2 = { 3, 4 };
        printf("Arrays: %s and %s ==> Median: %.1f\n",
                java.util."[array]", java.util."[array]", findMedianSortedArrays(a2, b2));

        int* a3 = { 0, 0 };
        int* b3 = { 0, 0 };
        printf("Arrays: %s and %s ==> Median: %.1f\n",
                java.util."[array]", java.util."[array]", findMedianSortedArrays(a3, b3));
        return 0;
}

/*
 * Time Complexity: O(log(min(M, N))) - Binary search on the shorter array.
 * Space Complexity: O(1) - Constant stack registers.
 */
