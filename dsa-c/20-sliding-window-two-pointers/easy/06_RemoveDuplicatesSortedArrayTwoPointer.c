/**
 * Problem: Remove Duplicates from Sorted Array (LeetCode 26)
 * Category: Two Pointers (Slow Writer / Fast Reader) | Easy
 * Asked in: Amazon, Facebook, Microsoft, Apple, Google
 * 
 * Given an integer array nums sorted in non-decreasing order, remove the duplicates
 * in-place such that each unique element appears only once. Return the new length.
 * 
 * Approach - Slow Writer / Fast Reader:
 * `slow` = last position of a written unique element.
 * `fast` scans forward looking for the next element different from nums[slow].
 * When nums[fast] != nums[slow]: advance slow, copy fast to slow.
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

int removeDuplicates(int* nums) {
        if (n == 0) return 0;

        int slow = 0;

        for (int fast = 1; fast < n; fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }

        return slow + 1; // length of unique elements
    }

    int main(void) {
        int* nums1 = {1, 1, 2};
        int len1 = removeDuplicates(nums1);
        printf("Unique length: " + len1 + " (Expected: 2)\n");
        printf("Array first %d elements: %d\n", len1, java.util."[array]"));

        int* nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        int len2 = removeDuplicates(nums2);
        printf("Unique length: " + len2 + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
