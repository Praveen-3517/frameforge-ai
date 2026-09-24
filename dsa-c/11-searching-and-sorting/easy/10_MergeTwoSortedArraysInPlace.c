/*
 * Problem Statement:
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing order,
 * and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 * The final sorted array should not be returned by the function, but instead be stored inside
 * the array nums1. To accommodate this, nums1 has a length of m + n.
 * (LeetCode 88: Merge Sorted Array)
 * 
 * Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * 
 * Asked in: Facebook/Meta, Microsoft, Amazon, Google, Bloomberg
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
     * Three-Pointer Merging from Backward:
     * Start from the tail of nums1 (index m + n - 1):
     * Place the larger of nums1[p1] and nums2[p2] at nums1[p].
     * Avoids overwriting existing elements in nums1 without requiring an auxiliary array!
     */
    void merge(int* nums1, int m, int* nums2, int n) {
        int p1 = m - 1;
        int p2 = n - 1;
        int p = m + n - 1;

        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;
        }

        // Fill remaining elements of nums2 if any
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }

    int main(void) {
        int* nums1 = {1, 2, 3, 0, 0, 0};
        int m = 3;
        int* nums2 = {2, 5, 6};
        int n = 3;

        printf("nums1: [array], m = %d\n", m);
        printf("nums2: [array], n = %d\n", n);

        merge(nums1, m, nums2, n);
        printf("Merged nums1: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(m + n) - Single pass filling buffer from back.
 * Space Complexity: O(1) in-place merging.
 */
