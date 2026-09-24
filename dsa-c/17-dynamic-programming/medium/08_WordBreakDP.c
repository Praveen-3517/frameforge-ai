/**
 * Problem: Word Break (LeetCode 139)
 * Asked in: Facebook, Amazon, Google, Bloomberg, Apple
 * 
 * Given a string s and a dictionary of strings wordDict, return true if s can be
 * segmented into a space-separated sequence of one or more dictionary words.
 * 
 * Approach:
 * 1D Dynamic Programming:
 * Let dp[i] be true if prefix s[0..i-1] can be segmented using dictionary words.
 * - Base case: dp[0] = true (empty string).
 * - For i from 1 to s.length():
 *   - For j from 0 to i - 1:
 *     - If dp[j] is true and wordDict contains s.substring(j, i):
 *       dp[i] = true, break.
 * 
 * Time Complexity: O(N^2 * L) where N is s.length() and L is max word length.
 * Space Complexity: O(N) for DP array + O(Dict) for HashSet.
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

bool wordBreak(const char* s, int* wordDict) {
        Set<const char*> wordSet = new HashSet<>(wordDict);
        int n = ((int)strlen(s));
        bool[] dp = (bool*)malloc((n + 1) * sizeof(bool));
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.contains(s.substring(j, i))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }

    int main(void) {
        printf("leetcode: " + wordBreak("leetcode", Arrays.asList("leet", "code")) + " (Expected: true)\n");
        printf("applepenapple: " + wordBreak("applepenapple", Arrays.asList("apple", "pen")) + " (Expected: true)\n");
        printf("catsandog: " + wordBreak("catsandog", Arrays.asList("cats", "dog", "sand", "and", "cat")) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
