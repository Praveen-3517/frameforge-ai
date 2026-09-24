/**
 * Problem Statement:
 * Given an array of integers `nums` and an integer `target`, return indices of the two numbers
 * such that they add up to target.
 * Assume exactly one valid solution exists, and you may not use the same element twice.
 * (LeetCode 1: Two Sum).
 *
 * Example:
 * nums = [2, 7, 11, 15], target = 9 -> [0, 1]
 *
 * Asked in: Google, Amazon, Facebook / Meta, Apple, Microsoft (The #1 Most Asked Question)
 *
 * Approach:
 * - Method 1: Brute Force (O(N^2) Time, O(1) Space):
 *   Nested loops checking all pairs `(i, j)`.
 * - Method 2: One-Pass HashMap (O(N) Time, O(N) Space):
 *   For each element `nums[i]`:
 *   - The required complement is `complement = target - nums[i]`.
 *   - Check if `complement` is already in the hash map.
 *   - If found, return `[map.get(complement), i]`.
 *   - Otherwise, store `map.put(nums[i], i)` and proceed.
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

// Optimal One-Pass HashMap: O(N) Time, O(N) Space
    int* twoSum(int* nums, int target) {
        Map<int, int> map = new HashMap<>();

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];

            if (map.containsKey(complement)) {
                return (int[]){ map.get(complement), i };
            }

            map.put(nums[i], i);
        }

        return (int*)malloc((0) * sizeof(int));
    }

    int main(void) {
        printf("=== LeetCode 1: Two Sum (One-Pass HashMap O(N)) ===\n");

        int* nums = { 2, 7, 11, 15 };
        int target = 9;

        int* result = twoSum(nums, target);
        printf("Array : " + "[array]\n");
        printf("Target: %d\n", target);
        printf("Indices: %s (Values: %d + %d = %d)\n",
                "[array]", nums[result[0]], nums[result[1]], target);
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass over the array with O(1) average hash lookups.
 * Space Complexity: O(N) - Storage for up to N entries in the hash map.
 */
