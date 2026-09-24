/**
 * Problem: Palindrome Partitioning II (LeetCode 132)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Approach:
 * 1. Precompute Palindromic Substrings:
 *    isPal[i][j] is true if s[i..j] is a palindrome:
 *    isPal[i][j] = (s[i] == s[j]) && (j - i <= 2 || isPal[i + 1][j - 1]).
 * 2. 1D DP for Minimum Cuts:
 *    Let cuts[i] be the minimum cuts needed for prefix s[0..i].
 *    - If isPal[0][i] is true: cuts[i] = 0 (no cuts needed!).
 *    - Otherwise, cuts[i] = min_{0 <= j < i and isPal[j + 1][i]} (cuts[j] + 1).
 * 
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2) for palindrome table and cuts array.
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

int minCut(const char* s) {
        int n = ((int)strlen(s));
        bool[][] isPal = (bool*)malloc((n) * sizeof(bool))[n];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        int* cuts = (int*)malloc((n) * sizeof(int));
        for (int i = 0; i < n; i++) {
            if (isPal[0][i]) {
                cuts[i] = 0;
            } else {
                cuts[i] = i; // worst case: cut every character
                for (int j = 0; j < i; j++) {
                    if (isPal[j + 1][i]) {
                        cuts[i] = MIN(cuts[i], cuts[j] + 1);
                    }
                }
            }
        }

        return cuts[n - 1];
    }

    int main(void) {
        printf("Min cuts for 'aab': " + minCut("aab") + " (Expected: 1)\n"); // "aa" | "b"
        printf("Min cuts for 'a': " + minCut("a") + " (Expected: 0)\n");
        printf("Min cuts for 'ab': " + minCut("ab") + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
