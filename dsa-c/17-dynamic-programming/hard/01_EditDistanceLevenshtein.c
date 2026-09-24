/**
 * Problem: Edit Distance / Levenshtein Distance (LeetCode 72)
 * Asked in: Google, Amazon, Microsoft, Facebook
 * 
 * Given two strings word1 and word2, return the minimum number of operations required
 * to convert word1 to word2.
 * You have the following three operations permitted on a word:
 * 1. Insert a character
 * 2. Delete a character
 * 3. Replace a character
 * 
 * Approach:
 * 2D Dynamic Programming:
 * dp[i][j] represents min edit distance between word1[0..i-1] and word2[0..j-1].
 * - If word1[i-1] == word2[j-1]: dp[i][j] = dp[i-1][j-1]
 * - Else: dp[i][j] = 1 + min(
 *       dp[i][j-1],    // Insert
 *       dp[i-1][j],    // Delete
 *       dp[i-1][j-1]   // Replace
 *   )
 * 
 * Time Complexity: O(M * N) where M = word1.length(), N = word2.length().
 * Space Complexity: O(M * N)
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

int minDistance(const char* word1, const char* word2) {
        int m = ((int)strlen(word1));
        int n = ((int)strlen(word2));
        int** dp = (int*)malloc((m + 1) * sizeof(int))[n + 1];

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + MIN(dp[i - 1][j - 1], // Replace
                                    Math.min(dp[i - 1][j],   // Delete
                                             dp[i][j - 1])); // Insert
                }
            }
        }

        return dp[m][n];
    }

    int main(void) {
        printf("horse -> ros: " + minDistance("horse", "ros") + " (Expected: 3)\n");
        printf("intention -> execution: " + minDistance("intention", "execution") + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
