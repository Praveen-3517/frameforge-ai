/**
 * Problem Statement:
 * Given an input string `s` and a pattern `p`, implement wildcard pattern matching with support
 * for '?' and '*' where:
 *   - '?' Matches any single character.
 *   - '*' Matches any sequence of characters (including the empty sequence).
 * (LeetCode 44: Wildcard Matching - Hard).
 *
 * Example:
 * s = "aa", p = "a"   -> false
 * s = "aa", p = "*"   -> true
 * s = "cb", p = "?a"  -> false
 * s = "adceb", p = "*a*b" -> true
 *
 * Asked in: Facebook / Meta, Google, Microsoft, Amazon
 *
 * Approach 1: 2D Dynamic Programming (O(M * N) Time, O(M * N) Space):
 * - `dp[i][j]` is true if `s[0..i-1]` matches `p[0..j-1]`.
 * - Base Case: `dp[0][0] = true`. If pattern starts with '*', `dp[0][j] = dp[0][j - 1]`.
 * - Transitions:
 *   - If `p[j-1] == '?' || p[j-1] == s[i-1]`:
 *     `dp[i][j] = dp[i - 1][j - 1]`
 *   - If `p[j-1] == '*'`:
 *     `dp[i][j] = dp[i][j - 1] || dp[i - 1][j]`
 *     (where `dp[i][j-1]` treats '*' as matching 0 characters,
 *      and `dp[i-1][j]` treats '*' as matching 1 or more characters).
 *
 * Approach 2: Greedy Two-Pointer Backtracking (O(M * N) Worst Case, O(1) Space):
 * - Save the last position of '*' (`starIdx`) and the corresponding index in `s` (`matchIdx`).
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

// Approach 1: Dynamic Programming
    bool isMatchDP(const char* s, const char* p) {
        int m = ((int)strlen(s));
        int n = ((int)strlen(p));
        bool[][] dp = (bool*)malloc((m + 1) * sizeof(bool))[n + 1];

        dp[0][0] = true;

        // Initialize pattern matching empty string
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sc = s[i - 1];
                char pc = p[j - 1];

                if (pc == '?' || pc == sc) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (pc == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }

    // Approach 2: Greedy Two-Pointer (O(1) Space)
    bool isMatchGreedy(const char* s, const char* p) {
        int sIdx = 0, pIdx = 0;
        int starIdx = -1, matchIdx = 0;

        while (sIdx < ((int)strlen(s))) {
            if (pIdx < ((int)strlen(p)) && (p[pIdx] == '?' || p[pIdx] == s[sIdx])) {
                sIdx++;
                pIdx++;
            } else if (pIdx < ((int)strlen(p)) && p[pIdx] == '*') {
                starIdx = pIdx;
                matchIdx = sIdx;
                pIdx++; // Hypothesize '*' matches 0 characters
            } else if (starIdx != -1) {
                // Backtrack: expand '*' to match one more character
                pIdx = starIdx + 1;
                matchIdx++;
                sIdx = matchIdx;
            } else {
                return false;
            }
        }

        // Consume remaining '*' in pattern
        while (pIdx < ((int)strlen(p)) && p[pIdx] == '*') {
            pIdx++;
        }

        return pIdx == ((int)strlen(p));
    }

    int main(void) {
        printf("=== LeetCode 44: Wildcard Matching (DP vs Greedy O(1)) ===\n");

        const char*[][] testCases = {
            { "aa", "a" },
            { "aa", "*" },
            { "cb", "?a" },
            { "adceb", "*a*b" },
            { "acdcb", "a*c?b" }
        };

        for (const char*[] tc : testCases) {
            bool ansDP = isMatchDP(tc[0], tc[1]);
            bool ansGreedy = isMatchGreedy(tc[0], tc[1]);
            printf("s: %-8s | p: %-8s ==> DP: %-5s | Greedy: %-5s\n",
                    "\"" + tc[0] + "\"", "\"" + tc[1] + "\"", ansDP, ansGreedy);
        }
        return 0;
}

/*
 * Time Complexity: O(M * N) for DP, O(M * N) worst-case (average O(N)) for Greedy.
 * Space Complexity: O(M * N) for DP table, O(1) for Greedy.
 */
