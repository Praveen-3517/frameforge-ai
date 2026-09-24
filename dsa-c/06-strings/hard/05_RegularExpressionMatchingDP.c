/**
 * Problem Statement:
 * Given an input string `s` and a pattern `p`, implement regular expression matching with support
 * for '.' and '*' where:
 *   - '.' Matches any single character.
 *   - '*' Matches zero or more of the PRECEDING element.
 * The matching should cover the entire input string (not partial).
 * (LeetCode 10: Regular Expression Matching - Hard).
 *
 * Example:
 * s = "aa", p = "a"   -> false
 * s = "aa", p = "a*"  -> true
 * s = "ab", p = ".*"  -> true
 *
 * Asked in: Google, Facebook / Meta, Amazon, Microsoft, Apple
 *
 * Approach:
 * - 2D Dynamic Programming (O(M * N) Time & Space):
 *   `dp[i][j]` represents whether `s[0..i-1]` matches `p[0..j-1]`.
 *   - Base Case: `dp[0][0] = true` (empty string matches empty pattern).
 *   - Patterns matching empty string:
 *     For `j` from 2 to n: if `p[j-1] == '*'`: `dp[0][j] = dp[0][j - 2]` (e.g. "a*", "a*b*").
 *   - Transitions:
 *     - If `p[j-1] == '.' || p[j-1] == s[i-1]`:
 *       `dp[i][j] = dp[i - 1][j - 1]`
 *     - If `p[j-1] == '*'`:
 *       1. Zero occurrences of preceding char `p[j-2]`:
 *          `dp[i][j] = dp[i][j - 2]`
 *       2. One or more occurrences of preceding char:
 *          If `p[j-2] == '.' || p[j-2] == s[i-1]`:
 *            `dp[i][j] = dp[i][j] || dp[i - 1][j]`
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

bool isMatch(const char* s, const char* p) {
        int m = ((int)strlen(s));
        int n = ((int)strlen(p));
        bool[][] dp = (bool*)malloc((m + 1) * sizeof(bool))[n + 1];

        dp[0][0] = true;

        // Deal with patterns with '*' matching empty string s
        for (int j = 2; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sc = s[i - 1];
                char pc = p[j - 1];

                if (pc == '.' || pc == sc) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (pc == '*') {
                    // Option 1: 0 occurrences of preceding char
                    dp[i][j] = dp[i][j - 2];

                    // Option 2: 1 or more occurrences
                    char prevChar = p[j - 2];
                    if (prevChar == '.' || prevChar == sc) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }

    int main(void) {
        printf("=== LeetCode 10: Regular Expression Matching (2D DP) ===\n");

        const char*[][] testCases = {
            { "aa", "a" },
            { "aa", "a*" },
            { "ab", ".*" },
            { "aab", "c*a*b" },
            { "mississippi", "mis*is*p*." }
        };

        for (const char*[] tc : testCases) {
            bool match = isMatch(tc[0], tc[1]);
            printf("s: %-15s | p: %-15s ==> Match: %s\n",
                    "\"" + tc[0] + "\"", "\"" + tc[1] + "\"", match);
        }
        return 0;
}

/*
 * Time Complexity: O(M * N) - Computes each cell in the (M+1) x (N+1) DP matrix once.
 * Space Complexity: O(M * N) - DP state table.
 */
