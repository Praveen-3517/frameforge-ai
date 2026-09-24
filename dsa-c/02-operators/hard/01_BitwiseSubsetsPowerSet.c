/**
 * Problem Statement:
 * Given an integer array `nums` of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * Solve this iteratively using bit manipulation and binary bitmasks.
 * (LeetCode 78: Subsets).
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Google, Bloomberg
 *
 * Approach:
 * - Binary Representation of Subsets:
 *   An array with N elements has 2^N distinct subsets.
 *   Each subset corresponds to a unique integer `mask` in the range [0, 2^N - 1].
 * - The i-th bit of `mask` determines whether element `nums[i]` is included in that subset:
 *   - If `(mask & (1 << i)) != 0`, include `nums[i]`.
 *   - Otherwise, exclude `nums[i]`.
 * - Time Complexity: O(N * 2^N) to build all subsets.
 *   Space Complexity: O(N * 2^N) for output storage.
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
        int totalSubsets = 1 << n; // 2^N subsets
        int*> result = new ArrayList<>(totalSubsets);

        for (int mask = 0; mask < totalSubsets; mask++) {
            int* currentSubset = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                // Check if the i-th bit is set in mask
                if ((mask & (1 << i)) != 0) {
                    currentSubset.add(nums[i]);
                }
            }
            result.add(currentSubset);
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 78: Power Set Generation via Bitmasks ===\n");

        int* nums = { 1, 2, 3 };
        int*> allSubsets = subsets(nums);

        printf("Input Array: " + java.util."[array]\n");
        printf("Total Subsets (2^%d = %d):\n", n, allSubsets.size());

        for (int i = 0; i < allSubsets.size(); i++) {
            const char* binaryMask = const char*.format("%3s", toBinaryString(i)).replace(' ', '0');
            printf("  Mask [%s] (%2d) ==> %s\n", binaryMask, i, allSubsets.get(i));
        }
        return 0;
}

/*
 * Time Complexity: O(N * 2^N) - Iterate through 2^N bitmasks, each checking N bits.
 * Space Complexity: O(N * 2^N) - Memory required to store all subsets.
 */
