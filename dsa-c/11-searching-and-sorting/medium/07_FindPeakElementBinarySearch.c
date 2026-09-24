/*
 * Problem Statement:
 * A peak element is an element that is strictly greater than its neighbors.
 * Given a 0-indexed integer array nums, find a peak element, and return its index.
 * If the array contains multiple peaks, return the index to any of the peaks.
 * You may imagine that nums[-1] = nums[n] = -infinity.
 * You must write an algorithm that runs in O(log n) time.
 * (LeetCode 162: Find Peak Element)
 * 
 * Example:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 5 (nums[5] == 6 is greater than its neighbors 5 and 4)
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
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
     * Binary Search on Slopes:
     * - Compare nums[mid] with nums[mid + 1]:
     *   - If nums[mid] < nums[mid + 1]: We are on an upward slope. A peak is guaranteed
     *     to exist to the right (low = mid + 1).
     *   - If nums[mid] > nums[mid + 1]: We are on a downward slope. A peak is guaranteed
     *     to exist at mid or to the left (high = mid).
     * - Terminate when low == high.
     */
    int findPeakElement(int* nums) {
        int low = 0;
        int high = n - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] < nums[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }

    int main(void) {
        int* nums = {1, 2, 1, 3, 5, 6, 4};

        int peakIdx = findPeakElement(nums);
        printf("Array: [1, 2, 1, 3, 5, 6, 4]\n");
        printf("Peak found at index %d (value = %d)\n", peakIdx, nums[peakIdx]);
        return 0;
}

/*
 * Time Complexity: O(log N) binary search steps.
 * Space Complexity: O(1) auxiliary space.
 */
