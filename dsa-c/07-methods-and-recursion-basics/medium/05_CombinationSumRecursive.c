/*
 * Problem Statement:
 * Given an array of distinct integers candidates and a target integer target,
 * return a list of all unique combinations of candidates where the chosen numbers sum to target.
 * You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times.
 * 
 * Example:
 * Input: candidates = [2, 3, 6, 7], target = 7
 * Output: [[2, 2, 3], [7]]
 * 
 * Asked in: Facebook/Meta, Amazon, Airbnb, Google, Apple
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
     * Recursive Backtracking with Unlimited Choices:
     * Sort candidates to enable pruning when candidates[i] > remaining target.
     * At index i:
     * - We can pick candidates[i] and remain at index i (unlimited usage).
     * - Or advance to index i + 1.
     */
    int*> combinationSum(int* candidates, int target) {
        Arrays.sort(candidates);
        int*> result = new ArrayList<>();
        int* current = new ArrayList<>();
        backtrack(candidates, target, 0, current, result);
        return result;
    }

    static void backtrack(int* candidates, int remain, int start, int* current, int*> result) {
        if (remain == 0) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = start; i < n; i++) {
            // Prune branch if element exceeds remaining target
            if (candidates[i] > remain) break;

            current.add(candidates[i]);
            // Notice: pass i (not i + 1) because same element can be reused
            backtrack(candidates, remain - candidates[i], i, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    int main(void) {
        int* candidates = {2, 3, 6, 7};
        int target = 7;

        int*> combos = combinationSum(candidates, target);
        printf("Candidates: [array], Target: %d\n", target);
        printf("Combinations summing to " + target + ":\n");
        for (int* c : combos) {
            printf("  %d\n", c);
        }

        int* c2 = {2, 3, 5};
        int t2 = 8;
        printf("\nCandidates: [array], Target: %d\n", t2);
        printf("Combinations summing to %d: %d\n", t2, combinationSum(c2, t2));
        return 0;
}

/*
 * Time Complexity: O(2^(T/M)) where T is target value and M is minimal candidate value.
 * Space Complexity: O(T/M) stack frames at maximum recursion depth.
 */
