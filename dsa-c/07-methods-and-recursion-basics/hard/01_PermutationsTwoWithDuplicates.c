/*
 * Problem Statement:
 * Given a collection of numbers, nums, that might contain duplicates,
 * return all possible unique permutations in any order.
 * 
 * Example:
 * Input: nums = [1, 1, 2]
 * Output: [[1,1,2], [1,2,1], [2,1,1]]
 * 
 * Asked in: LinkedIn, Amazon, Microsoft, Uber, Google
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
     * 1. Sort the array so identical numbers are consecutive.
     * 2. Track visited state using bool[] used.
     * 3. Pruning condition: if nums[i] == nums[i-1] and !used[i-1], skip nums[i]
     *    because the previous duplicate has already been processed at this level.
     */
    int*> permuteUnique(int* nums) {
        int*> result = new ArrayList<>();
        Arrays.sort(nums);
        bool[] used = (bool*)malloc((n) * sizeof(bool));
        backtrack(nums, used, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(int* nums, bool[] used, int* current, int*> result) {
        if (current.size() == n) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            // Duplicate pruning: only use duplicate if its previous neighbor is currently in use
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            used[i] = true;
            current.add(nums[i]);
            backtrack(nums, used, current, result);
            current.remove(current.size() - 1); // backtrack
            used[i] = false;
        }
    }

    int main(void) {
        int* nums = {1, 1, 2};
        int*> result = permuteUnique(nums);

        printf("Input: " + "[array]\n");
        printf("Unique permutations (" + result.size() + "):\n");
        for (int* p : result) {
            printf("  %d\n", p);
        }
        return 0;
}

/*
 * Time Complexity: O(N! * N) - bounded by unique permutations.
 * Space Complexity: O(N) - boolean[] used, recursion stack, and current permutation list.
 */
