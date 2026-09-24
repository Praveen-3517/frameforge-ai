/**
 * Problem: Jump Game (LeetCode 55)
 * Asked in: Amazon, Google, Microsoft, Apple
 * 
 * You are given an integer array nums. You are initially positioned at the array's first index,
 * and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 * 
 * Approach:
 * Greedy Max Reachable Horizon:
 * Track maxReach: the farthest index we can reach so far.
 * - At each index i:
 *   - If i > maxReach, we can never reach this index -> return false.
 *   - Update maxReach = max(maxReach, i + nums[i]).
 *   - If maxReach >= nums.length - 1, return true.
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

bool canJump(int* nums) {
        int maxReach = 0;

        for (int i = 0; i < n; i++) {
            if (i > maxReach) {
                return false;
            }
            maxReach = MAX(maxReach, i + nums[i]);
            if (maxReach >= n - 1) {
                return true;
            }
        }

        return true;
    }

    int main(void) {
        int* nums1 = {2, 3, 1, 1, 4};
        printf("Can jump 1: " + canJump(nums1) + " (Expected: true)\n");

        int* nums2 = {3, 2, 1, 0, 4};
        printf("Can jump 2: " + canJump(nums2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
