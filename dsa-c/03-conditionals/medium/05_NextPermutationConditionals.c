/**
 * Problem Statement:
 * A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
 * Given an array of integers `nums`, find the next lexicographically greater permutation.
 * If no such permutation is possible, rearrange it as the lowest possible order (sorted in ascending order).
 * Must be done in-place using O(1) extra memory.
 * (LeetCode 31: Next Permutation).
 *
 * Asked in: Google, Amazon, Facebook / Meta, Microsoft
 *
 * Approach:
 * - 3-Step Lexicographical Boundary Conditionals:
 *   1. Step 1 (Find Pivot):
 *      Traverse backwards from right-to-left to find the first index `i` where `nums[i] < nums[i + 1]`.
 *      Everything to the right of `i` is currently in non-increasing order.
 *   2. Step 2 (Find Successor & Swap):
 *      If such a pivot `i >= 0` exists:
 *      Traverse backwards from right-to-left again to find the smallest number larger than `nums[i]`:
 *      first index `j` where `nums[j] > nums[i]`.
 *      Swap `nums[i]` and `nums[j]`.
 *   3. Step 3 (Reverse Suffix):
 *      Reverse the subarray from `i + 1` to the end of the array to minimize the suffix.
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

void nextPermutation(int* nums) {
        if (nums == NULL || n <= 1) return;

        int n = n;
        int i = n - 2;

        // Step 1: Find first decreasing element from right
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // Step 2: If pivot found, find next larger element to swap
        if (i >= 0) {
            int j = n - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            swap(nums, i, j);
        }

        // Step 3: Reverse the suffix from i + 1 to n - 1
        reverse(nums, i + 1, n - 1);
    }

    static void swap(int* nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    static void reverse(int* nums, int left, int right) {
        while (left < right) {
            swap(nums, left++, right--);
        }
    }

    int main(void) {
        printf("=== LeetCode 31: Next Permutation (In-Place Lexicographical Flow) ===\n");

        int** testCases = {
            { 1, 2, 3 },      // -> [1, 3, 2]
            { 3, 2, 1 },      // -> [1, 2, 3] (wraps around)
            { 1, 1, 5 },      // -> [1, 5, 1]
            { 1, 3, 5, 4, 2 } // -> [1, 4, 2, 3, 5]
        };

        for (int* arr : testCases) {
            int* original = arr.clone();
            nextPermutation(arr);
            printf("Permutation: %s ==> Next: %s\n",
                    "[array]", "[array]");
        }
        return 0;
}

/*
 * Time Complexity: O(N) - At most two linear scans and one linear reverse pass.
 * Space Complexity: O(1) - In-place array mutations.
 */
