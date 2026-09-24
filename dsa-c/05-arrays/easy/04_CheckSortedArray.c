/**
 * Problem Statement:
 * Given an array `nums`, return true if the array was originally sorted in non-decreasing order,
 * then rotated some number of positions (including zero). Otherwise, return false.
 * (LeetCode 1752: Check if Array Is Sorted and Rotated).
 *
 * Example:
 * [3, 4, 5, 1, 2] -> true (rotated from [1, 2, 3, 4, 5])
 * [2, 1, 3, 4]    -> false
 * [1, 2, 3]       -> true (rotated 0 times)
 *
 * Asked in: Google, Microsoft, Amazon, Adobe
 *
 * Approach:
 * - Count Inversion Drops Modulo N:
 *   If an array is sorted in ascending order and then rotated, its elements wrap around circularly.
 *   There can be AT MOST ONE position where `nums[i] > nums[(i + 1) % n]`:
 *   - The single drop occurs at the pivot point where the largest element wraps back to the smallest.
 *   - If the array was already sorted without rotation, there is 0 drop (unless `nums[n-1] > nums[0]`, which is 1 drop).
 *   - If there is MORE than 1 drop (`count > 1`), it is impossible for the array to be a rotated sorted array.
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

bool check(int* nums) {
        if (nums == NULL || n <= 1) return true;

        int n = n;
        int dropCount = 0;

        for (int i = 0; i < n; i++) {
            // Circular comparison with next element
            if (nums[i] > nums[(i + 1) % n]) {
                dropCount++;
            }
        }

        return dropCount <= 1;
    }

    int main(void) {
        printf("=== LeetCode 1752: Check if Array Is Sorted and Rotated ===\n");

        int** testCases = {
            { 3, 4, 5, 1, 2 },
            { 2, 1, 3, 4 },
            { 1, 2, 3 },
            { 1, 1, 1 },
            { 2, 3, 4, 5, 1 },
            { 6, 10, 6 }
        };

        for (int* arr : testCases) {
            bool isSortedRotated = check(arr);
            printf("Array: %-16s ==> Sorted & Rotated: %s\n",
                    java.util."[array]", isSortedRotated);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass over the array of size N.
 * Space Complexity: O(1) - Constant stack space.
 */
