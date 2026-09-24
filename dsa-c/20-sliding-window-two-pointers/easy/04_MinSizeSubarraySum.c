/**
 * Problem: Minimum Size Subarray Sum (LeetCode 209)
 * Category: Variable-Size Sliding Window | Easy/Medium
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * Given an array of positive integers nums and a positive integer target, return the
 * minimal length of a subarray whose sum is >= target. If no such subarray exists, return 0.
 * 
 * Approach - Variable Sliding Window:
 * 1. Expand: add arr[right] to windowSum.
 * 2. Shrink: while windowSum >= target, record window size and remove arr[left].
 * 3. Move left forward to shrink the window.
 * 
 * This ensures we find the minimum length window satisfying the sum condition.
 * 
 * Time Complexity: O(N) amortized — each element enters and leaves the window once.
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

int minSubArrayLen(int target, int* nums) {
        int left = 0;
        int windowSum = 0;
        int minLength = INT_MAX;

        for (int right = 0; right < n; right++) {
            windowSum += nums[right];

            while (windowSum >= target) {
                minLength = MIN(minLength, right - left + 1);
                windowSum -= nums[left++]; // shrink window from left
            }
        }

        return minLength == INT_MAX ? 0 : minLength;
    }

    int main(void) {
        printf("Min length: " + minSubArrayLen(7, (int[]){2, 3, 1, 2, 4, 3}) + " (Expected: 2)\n");
        // [4, 3] has sum 7 with length 2
        printf("Min length: " + minSubArrayLen(4, (int[]){1, 4, 4}) + " (Expected: 1)\n");
        printf("Min length: " + minSubArrayLen(11, (int[]){1, 1, 1, 1, 1, 1, 1, 1}) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
