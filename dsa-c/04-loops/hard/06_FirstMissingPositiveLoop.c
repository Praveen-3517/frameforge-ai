/**
 * Problem Statement:
 * Given an unsorted integer array `nums`, return the smallest positive integer that is not present in `nums`.
 * Requirements:
 *   - You must implement an algorithm that runs in O(N) time.
 *   - You must use only O(1) auxiliary memory.
 * (LeetCode 41: First Missing Positive - Hard).
 *
 * Example:
 * nums = [3, 4, -1, 1] -> Output: 2
 * nums = [7, 8, 9, 11, 12] -> Output: 1
 *
 * Asked in: Amazon, Google, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Cyclic Sort Placement Loop:
 *   By the Pigeonhole Principle, the first missing positive integer MUST lie in the range `[1, n + 1]`.
 *   If we place each positive integer `x` (where `1 <= x <= n`) at its "home" index `x - 1`:
 *   - While `i < n`:
 *     If `nums[i]` is in range `[1, n]` and `nums[i] != nums[nums[i] - 1]`:
 *       Swap `nums[i]` with the number currently sitting at index `nums[i] - 1`.
 *     Else:
 *       Increment `i++`.
 *   - Each swap places at least one number into its correct final position.
 *     Thus, the while loop executes at most 2N total iterations!
 * - Second pass:
 *   The first index `i` where `nums[i] != i + 1` reveals that `i + 1` is missing!
 *   If all slots 0 to n - 1 are matched, return `n + 1`.
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
        int i = 0;

        // Cyclic sort placement loop
        while (i < n) {
            int targetIdx = nums[i] - 1;

            // Check if nums[i] can and should be placed at targetIdx
            if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[targetIdx]) {
                swap(nums, i, targetIdx);
            } else {
                i++;
            }
        }

        // Second pass: find first misplaced number
        for (int j = 0; j < n; j++) {
            if (nums[j] != j + 1) {
                return j + 1;
            }
        }

        return n + 1;
    }

    static void swap(int* nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    int main(void) {
        printf("=== LeetCode 41: First Missing Positive (Cyclic Sort Loop) ===\n");

        int** testArrays = {
            { 1, 2, 0 },
            { 3, 4, -1, 1 },
            { 7, 8, 9, 11, 12 },
            { 1 },
            { 2 },
            { 1, 2, 3, 4, 5 }
        };

        for (int* arr : testArrays) {
            int* original = arr.clone();
            int missing = firstMissingPositive(arr);
            printf("Array: %-18s ==> First Missing Positive: %d\n",
                    "[array]", missing);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Each number is swapped into its target index at most once.
 * Space Complexity: O(1) - Pure in-place cyclic sorting.
 */
