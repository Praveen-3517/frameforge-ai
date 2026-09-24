/*
 * Problem Statement:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example:
 * Input: nums = [1, 2, 3]
 * Output: [[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Apple, Uber
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
     * Recursive Pick / Don't Pick (Backtracking):
     * At each element at index i, we have 2 choices:
     * 1. Include nums[i] in the current subset.
     * 2. Do not include nums[i].
     * Base case: When index reaches n, add a snapshot of current subset to results.
     */
    int*> subsets(int* nums) {
        int*> result = new ArrayList<>();
        int* current = new ArrayList<>();
        backtrack(nums, 0, current, result);
        return result;
    }

    static void backtrack(int* nums, int index, int* current, int*> result) {
        if (index == n) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Choice 1: Include nums[index]
        current.add(nums[index]);
        backtrack(nums, index + 1, current, result);

        // Choice 2: Exclude nums[index] (backtrack)
        current.remove(current.size() - 1);
        backtrack(nums, index + 1, current, result);
    }

    int main(void) {
        int* nums = {1, 2, 3};
        int*> powerSet = subsets(nums);

        printf("Input: [1, 2, 3]\n");
        printf("Total subsets (2^N = %d): %d\n", (1 << n), powerSet.size());
        printf("Subsets:\n");
        for (int* subset : powerSet) {
            printf("  %d\n", subset);
        }
        return 0;
}

/*
 * Time Complexity: O(N * 2^N) - 2^N total subsets, each takes O(N) to copy into result list.
 * Space Complexity: O(N) - Recursion call stack and temporary list current storage.
 */
