/*
 * Problem Statement:
 * Given an array of positive integers nums and a target integer target,
 * return true if there exists a subset whose elements sum up exactly to target,
 * otherwise return false.
 * 
 * Example:
 * Input: nums = [3, 34, 4, 12, 5, 2], target = 9
 * Output: true (subset [4, 5] sums to 9)
 * 
 * Asked in: Amazon, Samsung, Adobe, Cisco
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

/**
     * Approach:
     * Recursive Pick / Don't Pick:
     * At index i:
     * - Include nums[i]: recurse with target - nums[i]
     * - Exclude nums[i]: recurse with target
     * Base cases:
     * - if target == 0: return true.
     * - if index == n or target < 0: return false.
     */
    bool hasSubsetSum(int* nums, int target) {
        return helper(nums, 0, target);
    }

    static bool helper(int* nums, int index, int target) {
        if (target == 0) return true;
        if (index == n || target < 0) return false;

        // Include or exclude
        return helper(nums, index + 1, target - nums[index]) ||
               helper(nums, index + 1, target);
    }

    int main(void) {
        int* nums = {3, 34, 4, 12, 5, 2};

        printf("Nums: [3, 34, 4, 12, 5, 2]\n");
        int* targets = {9, 30, 14, 100};

        for (size_t _idx = 0; _idx < sizeof(targets)/sizeof(targets[0]); _idx++) {
        int t = targets[_idx];
            printf("Subset summing to %3d exists? %b\n", t, hasSubsetSum(nums, t));
        }
        return 0;
}

/*
 * Time Complexity: O(2^N) in worst case exploration.
 * Space Complexity: O(N) recursion stack depth.
 */
