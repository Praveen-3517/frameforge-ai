/**
 * Problem: Subsets (LeetCode 78)
 * Asked in: Amazon, Facebook, Google, Microsoft, Bloomberg
 * 
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Approach - Bitmask Enumeration:
 * For an array of n elements, there are exactly 2^n subsets.
 * Each subset corresponds to a bitmask from 0 to 2^n - 1.
 * If bit j is set in mask i, include nums[j] in subset i.
 * 
 * Time Complexity: O(2^N * N)
 * Space Complexity: O(2^N * N)
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

int*> subsets(int* nums) {
        int n = n;
        int totalSubsets = 1 << n; // 2^n
        int*> result = new ArrayList<>();

        for (int mask = 0; mask < totalSubsets; mask++) {
            int* subset = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) != 0) {
                    subset.add(nums[j]);
                }
            }
            result.add(subset);
        }

        return result;
    }

    int main(void) {
        int* nums1 = {1, 2, 3};
        int*> res = subsets(nums1);
        printf("All subsets of [1,2,3]: %d\n", res);
        printf("Total: " + res.size() + " (Expected: 8)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
