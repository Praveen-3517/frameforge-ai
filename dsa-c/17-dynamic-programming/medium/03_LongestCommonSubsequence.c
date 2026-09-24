/**
 * Problem: Longest Common Subsequence (LeetCode 1143)
 * Asked in: Amazon, Microsoft, Google, Bloomberg
 * 
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * If there is no common subsequence, return 0.
 * 
 * Approach:
 * 2D Dynamic Programming:
 * Let dp[i][j] be LCS length of text1[0..i-1] and text2[0..j-1].
 * - If text1[i-1] == text2[j-1]:
 *     dp[i][j] = 1 + dp[i-1][j-1]
 * - Else:
 *     dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * 
 * Time Complexity: O(M * N) where M = text1.length(), N = text2.length().
 * Space Complexity: O(M * N) (or O(min(M, N)) with space optimization).
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

int longestCommonSubsequence(const char* text1, const char* text2) {
        int m = ((int)strlen(text1));
        int n = ((int)strlen(text2));
        int** dp = (int*)malloc((m + 1) * sizeof(int))[n + 1];

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = MAX(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }

    int main(void) {
        printf("LCS('abcde', 'ace'): " + longestCommonSubsequence("abcde", "ace") + " (Expected: 3)\n");
        printf("LCS('abc', 'abc'): " + longestCommonSubsequence("abc", "abc") + " (Expected: 3)\n");
        printf("LCS('abc', 'def'): " + longestCommonSubsequence("abc", "def") + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
