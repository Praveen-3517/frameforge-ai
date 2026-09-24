/*
 * Problem Statement:
 * Given two integers n and k, return all possible combinations of k numbers chosen
 * from the range [1, n]. You may return the answer in any order.
 * (LeetCode 77: Combinations)
 * 
 * Example:
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * 
 * Asked in: Google, Amazon, Microsoft, Apple
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
     * Backtracking with Pruning:
     * - Only pick numbers from `start` to `n`.
     * - Pruning optimization:
     *   We need `k - current.size()` more elements.
     *   If `n - i + 1 < k - current.size()`, there aren't enough elements left in the range,
     *   so we can safely stop iterating!
     */
    int*> combine(int n, int k) {
        int*> result = new ArrayList<>();
        backtrack(1, n, k, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(int start, int n, int k, int* current, int*> result) {
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Pruned loop condition
        int needed = k - current.size();
        for (int i = start; i <= n - needed + 1; i++) {
            current.add(i);
            backtrack(i + 1, n, k, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    int main(void) {
        int n = 4, k = 2;
        int*> combos = combine(n, k);

        printf("Combinations of " + k + " from [1.." + n + "] (Total: " + combos.size() + "):\n");
        printf("%d\n", combos);
        return 0;
}

/*
 * Time Complexity: O(k * C(n, k)) where C(n, k) is the binomial coefficient n choose k.
 * Space Complexity: O(k) for the current combination buffer and recursion stack.
 */
