/*
 * Problem Statement:
 * Given a collection of candidate numbers (candidates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sum to target.
 * Each number in candidates may only be used ONCE in the combination.
 * Note: The solution set must not contain duplicate combinations.
 * (LeetCode 40: Combination Sum II)
 * 
 * Example:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [
 *   [1,1,6],
 *   [1,2,5],
 *   [1,7],
 *   [2,6]
 * ]
 * 
 * Asked in: Amazon, Google, Microsoft, Facebook/Meta
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
     * Sort + Backtrack + Duplicate Pruning:
     * 1. Sort candidates.
     * 2. When candidates[i] > remaining target, break early (pruning).
     * 3. When i > start and candidates[i] == candidates[i-1], skip to prevent duplicate branch.
     * 4. Advance to i + 1 because each number can only be used once.
     */
    int*> combinationSum2(int* candidates, int target) {
        Arrays.sort(candidates);
        int*> result = new ArrayList<>();
        backtrack(candidates, target, 0, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(int* candidates, int remain, int start, int* current, int*> result) {
        if (remain == 0) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = start; i < n; i++) {
            if (candidates[i] > remain) break; // Prune branch

            // Skip duplicates at same recursion level
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            current.add(candidates[i]);
            backtrack(candidates, remain - candidates[i], i + 1, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    int main(void) {
        int* candidates = {10, 1, 2, 7, 6, 1, 5};
        int target = 8;

        int*> combos = combinationSum2(candidates, target);
        printf("Candidates: [array], Target: %d\n", target);
        printf("Combinations (" + combos.size() + "):\n");
        for (int* c : combos) {
            printf("  %d\n", c);
        }
        return 0;
}

/*
 * Time Complexity: O(2^N) bounded by number of subsets.
 * Space Complexity: O(N) recursion stack.
 */
