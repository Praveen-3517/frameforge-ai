/**
 * Problem: Distinct Subsequences (LeetCode 115)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 * 
 * Approach:
 * 1D Space-Optimized Dynamic Programming:
 * Let dp[j] be the number of distinct subsequences of s prefix that equal t[0..j-1].
 * - Base case: dp[0] = 1 (empty string t is formed by 1 subsequence: the empty one).
 * - For each character sChar in s:
 *   - Iterate backwards j from t.length() down to 1:
 *     - If sChar == t[j - 1]:
 *       dp[j] += dp[j - 1]
 * 
 * Time Complexity: O(M * N) where M = s.length(), N = t.length().
 * Space Complexity: O(N) using 1D array.
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

int numDistinct(const char* s, const char* t) {
        int m = ((int)strlen(s));
        int n = ((int)strlen(t));
        int* dp = (int*)malloc((n + 1) * sizeof(int));

        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            char sc = s[i];
            for (int j = n; j >= 1; j--) {
                if (sc == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n];
    }

    int main(void) {
        printf("Distinct 'rabbbit', 'rabbit': " + numDistinct("rabbbit", "rabbit") + " (Expected: 3)\n");
        printf("Distinct 'babgbag', 'bag': " + numDistinct("babgbag", "bag") + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
