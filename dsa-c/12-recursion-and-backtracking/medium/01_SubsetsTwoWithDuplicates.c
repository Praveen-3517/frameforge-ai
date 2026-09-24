/*
 * Problem Statement:
 * Given an integer array nums that may contain duplicates, return all possible subsets
 * (the power set). The solution set must not contain duplicate subsets.
 * Return the solution in any order.
 * (LeetCode 90: Subsets II)
 * 
 * Example:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * 
 * Asked in: Facebook/Meta, Amazon, Bloomberg, Microsoft
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
     * Backtracking with Duplicate Pruning:
     * 1. Sort the input array so duplicate numbers are adjacent.
     * 2. In loop starting from `start` to `n`:
     *    - If i > start and nums[i] == nums[i - 1], SKIP nums[i] to prevent duplicate subsets
     *      at the same recursive depth.
     */
    int*> subsetsWithDup(int* nums) {
        Arrays.sort(nums);
        int*> result = new ArrayList<>();
        backtrack(0, nums, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(int start, int* nums, int* current, int*> result) {
        result.add(new ArrayList<>(current));

        for (int i = start; i < n; i++) {
            // Duplicate pruning
            if (i > start && nums[i] == nums[i - 1]) continue;

            current.add(nums[i]);
            backtrack(i + 1, nums, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    int main(void) {
        int* nums = {1, 2, 2};
        int*> powerSet = subsetsWithDup(nums);

        printf("Array: [1, 2, 2]\n");
        printf("Unique subsets (" + powerSet.size() + "):\n");
        for (int* subset : powerSet) {
            printf("  %d\n", subset);
        }
        return 0;
}

/*
 * Time Complexity: O(N * 2^N) - At most 2^N subsets generated and copied.
 * Space Complexity: O(N) recursion stack and temporary list.
 */
