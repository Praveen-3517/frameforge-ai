/*
 * Problem Statement:
 * Given a sorted array of distinct integers and a target value, return the index if
 * the target is found. If not, return the index where it would be if it were inserted in order.
 * You must write an algorithm with O(log n) runtime complexity.
 * (LeetCode 35: Search Insert Position - Lower Bound)
 * 
 * Example 1:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 * 
 * Asked in: Google, Amazon, Apple, Microsoft
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
     * Lower Bound Binary Search:
     * If target found, return mid.
     * When loop terminates (low > high), `low` represents the smallest index
     * where nums[low] >= target (the exact insertion point).
     */
    int searchInsert(int* nums, int target) {
        int low = 0;
        int high = n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }

    int main(void) {
        int* nums = {1, 3, 5, 6};

        printf("Array: " + "[array]\n");
        int* targets = {5, 2, 7, 0};

        for (size_t _idx = 0; _idx < sizeof(targets)/sizeof(targets[0]); _idx++) {
        int t = targets[_idx];
            printf("Target %d -> Insertion index: %d\n", t, searchInsert(nums, t));
        }
        return 0;
}

/*
 * Time Complexity: O(log N) - Standard binary search.
 * Space Complexity: O(1) auxiliary space.
 */
