/*
 * Problem Statement:
 * Given an array of integers nums sorted in non-decreasing order, find the starting
 * and ending position of a given target value.
 * If target is not found in the array, return [-1, -1].
 * You must write an algorithm with O(log n) runtime complexity.
 * (LeetCode 34: Find First and Last Position of Element in Sorted Array)
 * 
 * Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3, 4]
 * 
 * Asked in: Facebook/Meta, Amazon, LinkedIn, Microsoft, Google
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
     * Dual Binary Search (Finding Left Bound and Right Bound):
     * - First search: finds first index of target by continuing search in left half when found.
     * - Second search: finds last index of target by continuing search in right half when found.
     */
    int* searchRange(int* nums, int target) {
        int first = findBound(nums, target, true);
        if (first == -1) return (int[]){-1, -1};
        int last = findBound(nums, target, false);
        return (int[]){first, last};
    }

    static int findBound(int* nums, int target, bool isFirst) {
        int low = 0;
        int high = n - 1;
        int bound = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                bound = mid;
                if (isFirst) {
                    high = mid - 1; // Keep searching left for earlier occurrence
                } else {
                    low = mid + 1;  // Keep searching right for later occurrence
                }
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return bound;
    }

    int main(void) {
        int* nums = {5, 7, 7, 8, 8, 10};

        printf("Array: " + "[array]\n");
        printf("Target 8: %d\n", "[array]"));
        printf("Target 6: %d\n", "[array]"));
        printf("Target 5: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(log N) - Two independent binary searches.
 * Space Complexity: O(1) auxiliary space.
 */
