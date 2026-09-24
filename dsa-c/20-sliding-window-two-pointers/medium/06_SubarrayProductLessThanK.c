/**
 * Problem: Subarray Product Less Than K (LeetCode 713)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * Given an array of integers nums and an integer k, return the number of contiguous
 * subarrays where the product of all the elements in the subarray is strictly less than k.
 * 
 * Approach - Variable Sliding Window:
 * Maintain window product. Expand right, multiply in nums[right].
 * While product >= k, divide out nums[left] and shrink left.
 * For each valid window of size (right - left + 1), there are exactly
 * (right - left + 1) subarrays ending at right (all right-aligned windows of various sizes).
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

int numSubarrayProductLessThanK(int* nums, int k) {
        if (k <= 1) return 0; // nothing can be < 1 with positive integers

        int left = 0;
        int product = 1;
        int count = 0;

        for (int right = 0; right < n; right++) {
            product *= nums[right];

            while (product >= k) {
                product /= nums[left++];
            }

            // Subarrays ending at right with left..right window all valid
            count += right - left + 1;
        }

        return count;
    }

    int main(void) {
        printf("%d (Expected: 8)\n", numSubarrayProductLessThanK((int[]){10, 5, 2, 6}, 100));
        // [10],[5],[2],[6],[10,5],[5,2],[2,6],[5,2,6] all < 100
        printf("%d (Expected: 0)\n", numSubarrayProductLessThanK((int[]){1, 2, 3}, 0));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
