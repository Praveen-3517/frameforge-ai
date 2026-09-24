/**
 * Problem: Move Zeroes (LeetCode 283)
 * Category: Two Pointers (Slow-Fast) | Easy
 * Asked in: Facebook, Amazon, Microsoft, Apple
 * 
 * Given an integer array nums, move all 0's to the end of it while maintaining the
 * relative order of the non-zero elements. Must modify in-place without making a copy.
 * 
 * Approach - Slow/Fast Two-Pointer:
 * `slow` tracks position to place next non-zero element.
 * `fast` scans through the array.
 * - When nums[fast] != 0: place at nums[slow], advance slow.
 * - Fill the remaining positions from slow to end with 0.
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

void moveZeroes(int* nums) {
        int slow = 0;

        // Move all non-zero elements to the front
        for (int fast = 0; fast < n; fast++) {
            if (nums[fast] != 0) {
                nums[slow++] = nums[fast];
            }
        }

        // Fill remaining positions with 0
        while (slow < n) {
            nums[slow++] = 0;
        }
    }

    int main(void) {
        int* arr1 = {0, 1, 0, 3, 12};
        moveZeroes(arr1);
        printf("%d (Expected: [1, 3, 12, 0, 0])\n", java.util."[array]");

        int* arr2 = {0};
        moveZeroes(arr2);
        printf("%d (Expected: [0])\n", java.util."[array]");

        int* arr3 = {1, 0, 0, 3, 0, 0, 11, 0, 5};
        moveZeroes(arr3);
        printf("%d\n", java.util."[array]");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
