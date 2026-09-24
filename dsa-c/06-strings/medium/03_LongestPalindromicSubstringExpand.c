/**
 * Problem Statement:
 * Given a string `s`, return the longest palindromic substring in `s`.
 * (LeetCode 5: Longest Palindromic Substring).
 *
 * Example:
 * s = "babad" -> "bab" (or "aba")
 * s = "cbbd"  -> "bb"
 *
 * Asked in: Amazon, Microsoft, Facebook / Meta, Google, Apple
 *
 * Approach:
 * - Expand Around Center (O(N^2) Time, O(1) Space):
 *   A palindrome mirrors around its center. There are 2N - 1 potential centers in a string of length N:
 *   - N single-character centers (odd-length palindromes, e.g. "aba" centered at 'b').
 *   - N - 1 two-character centers (even-length palindromes, e.g. "abba" centered between 'b' and 'b').
 *   For each index `i`:
 *   - Expand around odd center `(i, i)`
 *   - Expand around even center `(i, i + 1)`
 *   - Update global maximum substring coordinates `[start, start + maxLen]`.
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

const char* longestPalindrome(const char* s) {
        if (s == NULL || ((int)strlen(s)) < 2) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < ((int)strlen(s)); i++) {
            // Odd length palindrome
            int len1 = expandAroundCenter(s, i, i);
            // Even length palindrome
            int len2 = expandAroundCenter(s, i, i + 1);

            int len = MAX(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                // Calculate starting index of the palindrome
                start = i - (len - 1) / 2;
            }
        }

        return s.substring(start, start + maxLen);
    }

    static int expandAroundCenter(const char* s, int left, int right) {
        while (left >= 0 && right < ((int)strlen(s)) && s[left] == s[right]) {
            left--;
            right++;
        }
        // When loop exits, s[left] != s[right]. Valid palindrome was s[left+1 .. right-1]
        // Length = (right - 1) - (left + 1) + 1 = right - left - 1
        return right - left - 1;
    }

    int main(void) {
        printf("=== LeetCode 5: Longest Palindromic Substring (Expand Around Center) ===\n");

        const char*[] testStrings = { "babad", "cbbd", "a", "ac", "racecar", "forgeeksskeegfor" };

        for (const char* str : testStrings) {
            const char* lps = longestPalindrome(str);
            printf("const char*: %-20s ==> Longest Palindrome: \"%s\"\n",
                    "\"" + str + "\"", lps);
        }
        return 0;
}

/*
 * Time Complexity: O(N^2) - 2N centers expanded outwards.
 * Space Complexity: O(1) - Constant stack pointers.
 */
