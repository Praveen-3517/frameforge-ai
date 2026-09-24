/**
 * Problem Statement:
 * Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.
 * Solve in-place with O(1) extra space.
 * (LeetCode 189: Rotate Array).
 *
 * Example:
 * nums = [1, 2, 3, 4, 5, 6, 7], k = 3
 * Output: [5, 6, 7, 1, 2, 3, 4]
 *
 * Asked in: Amazon, Microsoft, Facebook / Meta, Bloomberg, Apple
 *
 * Approach:
 * - The 3-Reversal In-Place Algorithm:
 *   Let n = nums.length. Normalize `k = k % n`.
 *   Step 1: Reverse the entire array from 0 to n - 1:
 *           [1, 2, 3, 4, 5, 6, 7] -> [7, 6, 5, 4, 3, 2, 1]
 *   Step 2: Reverse the first k elements from 0 to k - 1:
 *           [7, 6, 5] -> [5, 6, 7]
 *   Step 3: Reverse the remaining n - k elements from k to n - 1:
 *           [4, 3, 2, 1] -> [1, 2, 3, 4]
 *   Combined result: [5, 6, 7, 1, 2, 3, 4]!
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

void rotate(int* nums, int k) {
        if (nums == NULL || n <= 1) return;

        int n = n;
        k = k % n;
        if (k == 0) return;

        // Step 1: Reverse entire array
        reverse(nums, 0, n - 1);
        // Step 2: Reverse first k elements
        reverse(nums, 0, k - 1);
        // Step 3: Reverse remaining elements
        reverse(nums, k, n - 1);
    }

    static void reverse(int* nums, int left, int right) {
        while (left < right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }

    int main(void) {
        printf("=== LeetCode 189: Rotate Array by K Places (3 Reversals) ===\n");

        int* nums = { 1, 2, 3, 4, 5, 6, 7 };
        int k = 3;

        printf("Original: " + "[array]\n");
        rotate(nums, k);
        printf("Rotated by %d steps: %s\n", k, "[array]");
        return 0;
}

/*
 * Time Complexity: O(N) - 3 partial reversals equate to 2N total element visits.
 * Space Complexity: O(1) - Pure in-place pointer swaps.
 */
