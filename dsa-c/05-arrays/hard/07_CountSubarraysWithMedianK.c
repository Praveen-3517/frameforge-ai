/**
 * Problem Statement:
 * You are given an array `nums` of size `n` consisting of distinct integers from 1 to `n`,
 * and a positive integer `k`.
 * Return the number of non-empty subarrays in `nums` that have a median equal to `k`.
 * (The median of an array of odd length is the middle element in sorted order;
 *  for even length, it is the left of the two middle elements).
 * (LeetCode 2448: Count Subarrays With Median K - Hard).
 *
 * Example:
 * nums = [3, 2, 1, 4, 5], k = 4 -> Output: 3 (subarrays [4], [4,5], and [1,4,5])
 *
 * Asked in: Google (Signature Array Hard)
 *
 * Approach:
 * - Value Transformation + Prefix Balance Frequency:
 *   1. Find index `pos` where `nums[pos] == k`.
 *   2. Any subarray having median `k` MUST contain `pos`!
 *   3. Transform array values into balance weights:
 *      `+1` if `val > k`, `-1` if `val < k`, `0` if `val == k`.
 *   4. A subarray containing `k` has median `k` if and only if the balance of elements
 *      (sum of +1 and -1) is:
 *      - `balance == 0` (for odd-length subarrays)
 *      - `balance == 1` (for even-length subarrays where median is the left of the two centers)
 *   5. Scan right from `pos` to `n - 1`:
 *      Track running balance, record frequencies in `Map<Integer, Integer> rightCounts`.
 *   6. Scan left from `pos` down to 0:
 *      Track running balance.
 *      To make total balance 0 (odd): we need `rightBalance = -leftBalance`.
 *      To make total balance 1 (even): we need `rightBalance = 1 - leftBalance`.
 *      Add matching counts to result!
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

int countSubarrays(int* nums, int k) {
        int n = n;
        int pos = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] == k) {
                pos = i;
                break;
            }
        }

        // Map rightBalance -> frequency
        Map<int, int> rightCounts = new HashMap<>();
        int runningRight = 0;

        for (int i = pos; i < n; i++) {
            if (nums[i] > k) runningRight++;
            else if (nums[i] < k) runningRight--;

            rightCounts.put(runningRight, rightCounts.getOrDefault(runningRight, 0) + 1);
        }

        int total = 0;
        int runningLeft = 0;

        for (int i = pos; i >= 0; i--) {
            if (nums[i] > k) runningLeft++;
            else if (nums[i] < k) runningLeft--;

            // Condition 1: Odd length (total balance == 0)
            total += rightCounts.getOrDefault(-runningLeft, 0);

            // Condition 2: Even length (total balance == 1)
            total += rightCounts.getOrDefault(1 - runningLeft, 0);
        }

        return total;
    }

    int main(void) {
        printf("=== LeetCode 2448: Count Subarrays With Median K ===\n");

        int* nums1 = { 3, 2, 1, 4, 5 };
        int k1 = 4;
        printf("Array: %s, k = %d ==> Subarrays with Median k: %d (Expected: 3)\n",
                java.util."[array]", k1, countSubarrays(nums1, k1));

        int* nums2 = { 2, 3, 1 };
        int k2 = 3;
        printf("Array: %s, k = %d ==> Subarrays with Median k: %d (Expected: 1)\n",
                java.util."[array]", k2, countSubarrays(nums2, k2));
        return 0;
}

/*
 * Time Complexity: O(N) - Two linear scans from pos to right and pos to left.
 * Space Complexity: O(N) - HashMap storing right suffix balance counts.
 */
