/**
 * Problem: Jump Game II (LeetCode 45)
 * Asked in: Amazon, Google, Microsoft, Apple
 * 
 * You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].
 * Each element nums[i] represents the maximum length of a forward jump from index i.
 * Return the minimum number of jumps to reach nums[n - 1].
 * 
 * Approach:
 * Implicit BFS / Greedy Window:
 * - Maintain two boundaries:
 *   - currentEnd: the farthest point reachable with current number of jumps.
 *   - farthest: the farthest point reachable with one additional jump.
 * - When index i reaches currentEnd, we MUST take another jump -> jumps++, currentEnd = farthest.
 * 
 * Time Complexity: O(N) single pass.
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

int jump(int* nums) {
        if (n <= 1) return 0;

        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; i++) {
            farthest = MAX(farthest, i + nums[i]);

            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                if (currentEnd >= n - 1) break;
            }
        }

        return jumps;
    }

    int main(void) {
        int* nums1 = {2, 3, 1, 1, 4};
        printf("Min jumps 1: " + jump(nums1) + " (Expected: 2)\n"); // jump to index 1, then to index 4

        int* nums2 = {2, 3, 0, 1, 4};
        printf("Min jumps 2: " + jump(nums2) + " (Expected: 2)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
