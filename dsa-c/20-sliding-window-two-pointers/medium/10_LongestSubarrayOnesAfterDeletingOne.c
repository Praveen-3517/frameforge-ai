/**
 * Problem: Longest Subarray of 1's After Deleting One Element (LeetCode 1493)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook
 * 
 * Given a binary array nums, you should delete one element from it.
 * Return the size of the longest non-empty subarray containing only 1's in the resulting array.
 * Return 0 if there is no such subarray.
 * 
 * Approach - Variable Window (At Most 1 Zero):
 * Maintain a window with at most one zero. When zeroCount > 1, shrink from left.
 * Answer = max window size - 1 (because we must delete exactly one element,
 * even if the window has no zeros, we delete one 1).
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

int longestSubarray(int* nums) {
        int left = 0;
        int zeroCount = 0;
        int maxLength = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) zeroCount++;

            while (zeroCount > 1) {
                if (nums[left++] == 0) zeroCount--;
            }

            // -1 because we must delete exactly one element from window
            maxLength = MAX(maxLength, right - left); // (right - left + 1) - 1
        }

        return maxLength;
    }

    int main(void) {
        printf("%d (Expected: 3)\n", longestSubarray((int[]){1, 1, 0, 1}));
        printf("%d (Expected: 5)\n", longestSubarray((int[]){0, 1, 1, 1, 0, 1, 1, 0, 1}));
        printf("%d (Expected: 2)\n", longestSubarray((int[]){1, 1, 1})); // must delete one '1'
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
