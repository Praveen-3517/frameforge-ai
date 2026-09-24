/*
 * Problem Statement:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Example:
 * Input: s = "aab"
 * Output: 1 (Partition ["aa", "b"] requires 1 cut)
 * 
 * Example 2:
 * Input: s = "a"
 * Output: 0
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
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
     * Memoized Recursion:
     * Let minCuts(i) be the minimum cuts required for substring s[i...n-1].
     * Base case: if i == n, return 0 cuts.
     * For every j from i to n - 1:
     *   if s[i...j] is palindrome:
     *     cuts = 1 + minCuts(j + 1)
     * Result is minCuts(0) - 1 (since k pieces need k - 1 cuts).
     */
    int minCut(const char* s) {
        int n = ((int)strlen(s));
        // Precompute palindrome table for O(1) checks
        bool[][] isPal = (bool*)malloc((n) * sizeof(bool))[n];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        int* memo = (int*)malloc((n) * sizeof(int));
        Arrays.fill(memo, -1);
        return solve(0, s, isPal, memo) - 1;
    }

    static int solve(int i, const char* s, bool[][] isPal, int* memo) {
        if (i == ((int)strlen(s))) return 0;
        if (memo[i] != -1) return memo[i];

        int minCost = INT_MAX;
        for (int j = i; j < ((int)strlen(s)); j++) {
            if (isPal[i][j]) {
                int cost = 1 + solve(j + 1, s, isPal, memo);
                minCost = MIN(minCost, cost);
            }
        }
        return memo[i] = minCost;
    }

    int main(void) {
        const char*[] testStrings = {"aab", "a", "ab", "racecar", "ababbbabbababa"};

        printf("--- Minimum Palindrome Partitioning Cuts ---\n");
        for (const char* s : testStrings) {
            printf("s = %-16s -> Min cuts: %d\n", "\"" + s + "\"", minCut(s));
        }
        return 0;
}

/*
 * Time Complexity: O(N^2) - Subproblem states N, each transitions up to N times.
 * Space Complexity: O(N^2) for palindrome lookup table and O(N) recursion stack.
 */
