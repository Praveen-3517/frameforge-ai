/**
 * Problem: Max Consecutive Ones III (LeetCode 1004)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Bloomberg, Facebook
 * 
 * Given a binary array nums and an integer k, return the maximum number of consecutive 1's
 * in the array if you can flip at most k 0's.
 * 
 * Approach - Variable Sliding Window (At Most K Zeros):
 * Maintain a window that contains at most k zeros.
 * Expand right; if nums[right] == 0, decrement k.
 * If k < 0 (exceeded flips), shrink from left:
 *   if nums[left] == 0, increment k back; advance left.
 * Track max window size.
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

int longestOnes(int* nums, int k) {
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < n; right++) {
            if (nums[right] == 0) k--;

            while (k < 0) {
                if (nums[left++] == 0) k++;
            }

            maxLength = MAX(maxLength, right - left + 1);
        }

        return maxLength;
    }

    int main(void) {
        printf("%d (Expected: 6)\n", longestOnes((int[]){1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2));
        // Flip 2 zeros at positions 9 and 10: window [1,1,1,1,0,1,1,1,1,1] -> 6 ones
        printf("%d (Expected: 10)\n", longestOnes((int[]){0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
