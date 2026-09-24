/**
 * Problem Statement:
 * Given an integer array `nums` sorted in non-decreasing order, remove the duplicates in-place
 * such that each unique element appears only once. The relative order of the elements should be kept the same.
 * Return `k`, the number of unique elements.
 * (LeetCode 26: Remove Duplicates from Sorted Array).
 *
 * Example:
 * nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
 * Output: k = 5, nums = [0, 1, 2, 3, 4, ...]
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Google, Apple
 *
 * Approach:
 * - Two-Pointer In-Place Compaction:
 *   - Pointer `k`: The write-pointer pointing to the position for the next unique element (starts at 1).
 *   - Pointer `i`: The read-pointer scanning through the array (starts at 1).
 *   - Invariant: Elements `nums[0..k-1]` are unique and sorted.
 *   - For each element `nums[i]`:
 *     If `nums[i] != nums[k - 1]`:
 *       `nums[k] = nums[i];`
 *       `k++;`
 *   - Return `k`.
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
        if (nums == NULL || n == 0) return 0;

        int k = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[k - 1]) {
                nums[k] = nums[i];
                k++;
            }
        }

        return k;
    }

    int main(void) {
        printf("=== LeetCode 26: Remove Duplicates from Sorted Array ===\n");

        int* nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
        printf("Original Array: " + "[array]\n");

        int k = removeDuplicates(nums);
        printf("Unique Element Count k: %d\n", k);
        printf("Compacted Array Prefix: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Single linear pass over the array.
 * Space Complexity: O(1) - Modifies the array strictly in-place.
 */
