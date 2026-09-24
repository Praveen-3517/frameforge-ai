/**
 * Problem Statement:
 * Given an unsorted integer array `nums`, return the smallest positive integer that is not present in `nums`.
 * Must run in O(N) time and use O(1) auxiliary memory.
 * (LeetCode 41: First Missing Positive - Hard).
 *
 * Asked in: Amazon, Google, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Cyclic Index Mapping (O(N) Time, O(1) Space):
 *   Array of length N can hold integers from 1 to N at index `0` to `N - 1`.
 *   Iterate through array:
 *   While `nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]`:
 *     Swap `nums[i]` and `nums[nums[i] - 1]`.
 *   Second pass:
 *     Return first `i + 1` where `nums[i] != i + 1`.
 *     If all 1..N are placed, return `n + 1`.
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

int firstMissingPositive(int* nums) {
        if (nums == NULL || n == 0) return 1;

        int n = n;

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                int targetIdx = nums[i] - 1;
                int temp = nums[i];
                nums[i] = nums[targetIdx];
                nums[targetIdx] = temp;
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }

    int main(void) {
        printf("=== LeetCode 41: First Missing Positive (Cyclic Array Indexing) ===\n");

        int** testArrays = {
            { 1, 2, 0 },
            { 3, 4, -1, 1 },
            { 7, 8, 9, 11, 12 },
            { 1, 2, 3 }
        };

        for (int* arr : testArrays) {
            int* orig = arr.clone();
            int ans = firstMissingPositive(arr);
            printf("Array: %-18s ==> First Missing: %d\n", "[array]", ans);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Each number is placed in its home index at most once.
 * Space Complexity: O(1) - Pure in-place cyclic index placement.
 */
