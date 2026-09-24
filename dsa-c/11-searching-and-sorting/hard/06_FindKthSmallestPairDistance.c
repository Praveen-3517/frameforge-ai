/*
 * Problem Statement:
 * The distance of a pair of integers a and b is defined as the absolute difference |a - b|.
 * Given an integer array nums and an integer k, return the k-th smallest distance among
 * all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.
 * (LeetCode 719: Find K-th Smallest Pair Distance)
 * 
 * Example:
 * Input: nums = [1,3,1], k = 1
 * Output: 0 (Pairs: (1,3) diff 2, (1,1) diff 0, (3,1) diff 2; 1st smallest distance is 0)
 * 
 * Asked in: Google, Citadel, Two Sigma
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
     * Binary Search on Pair Distance + Two-Pointer Sliding Window Count:
     * 1. Sort nums: O(N log N).
     * 2. The pair distance lies in range [0, nums[n-1] - nums[0]].
     * 3. For a guess distance 'mid', count how many pairs have distance <= mid
     *    in O(N) using two pointers:
     *    - For each right pointer, advance left pointer until nums[right] - nums[left] <= mid.
     *    - All pairs between left and right have distance <= mid: count += (right - left).
     * 4. If count >= k, candidate distance is viable; search left half (high = mid).
     *    Else, search right half (low = mid + 1).
     */
    int smallestDistancePair(int* nums, int k) {
        Arrays.sort(nums);
        int n = n;

        int low = 0;
        int high = nums[n - 1] - nums[0];

        while (low < high) {
            int mid = low + (high - low) / 2;

            int count = countPairsWithDistanceAtMost(nums, mid);
            if (count >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

    static int countPairsWithDistanceAtMost(int* nums, int dist) {
        int count = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {
            while (nums[right] - nums[left] > dist) {
                left++;
            }
            count += (right - left);
        }

        return count;
    }

    int main(void) {
        int* nums = {1, 3, 1};
        int k = 1;

        printf("Array: [1, 3, 1], k = 1\n");
        printf("1st smallest distance: %d\n", smallestDistancePair(nums, k));

        int* nums2 = {1, 1, 1};
        int k2 = 2;
        printf("\nArray: [1, 1, 1], k = 2\n");
        printf("2nd smallest distance: %d\n", smallestDistancePair(nums2, k2));
        return 0;
}

/*
 * Time Complexity: O(N log N + N log(maxDist))
 * Space Complexity: O(1) auxiliary space.
 */
