/**
 * Problem Statement:
 * You are given a string `s`. You can convert `s` to a palindrome by adding characters in front of it.
 * Return the shortest palindrome you can find by performing this transformation.
 * (LeetCode 214: Shortest Palindrome - Hard).
 *
 * Example:
 * s = "aacecaaa" -> Output: "aaacecaaa"
 * s = "abcd"     -> Output: "dcbabcd"
 *
 * Asked in: Google, Amazon, Microsoft, Apple
 *
 * Approach:
 * - KMP LPS Array on Mirrored String (O(N) Time, O(N) Space):
 *   To minimize added characters in front, we must find the LONGEST PALINDROMIC PREFIX of `s`.
 *   Any characters remaining after this prefix must be reversed and prepended in front.
 *   - Construct a combined string:
 *     `temp = s + '#' + reverse(s)`
 *     (The sentinel '#' ensures the prefix does not match across the boundary into the reverse part).
 *   - Compute the KMP LPS (Longest Proper Prefix which is also Suffix) array for `temp`.
 *   - The last element `lps[temp.length() - 1]` gives the exact length of the longest prefix of `s`
 *     that is simultaneously a suffix of `reverse(s)`.
 *     This length `L` is precisely the length of the longest palindromic prefix of `s`!
 *   - The non-palindromic suffix is `s.substring(L)`.
 *   - Final Answer: `new StringBuilder(suffix).reverse().toString() + s`.
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

const char* shortestPalindrome(const char* s) {
        if (s == NULL || ((int)strlen(s)) <= 1) return s;

        const char* rev = new StringBuilder(s).reverse().toString();
        const char* combined = s + "#" + rev;

        // Compute LPS array for combined string
        int m = ((int)strlen(combined));
        int* lps = (int*)malloc((m) * sizeof(int));
        int len = 0;
        int i = 1;

        while (i < m) {
            if (combined[i] == combined[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // Length of the longest palindromic prefix of s
        int palPrefixLen = lps[m - 1];

        // The remaining suffix must be reversed and prepended
        const char* nonPalSuffix = s.substring(palPrefixLen);
        const char* prefixToPrepend = new StringBuilder(nonPalSuffix).reverse().toString();

        return prefixToPrepend + s;
    }

    int main(void) {
        printf("=== LeetCode 214: Shortest Palindrome (KMP LPS Prefix Mirror) ===\n");

        const char*[] testStrings = { "aacecaaa", "abcd", "racecar", "banana", "a" };

        for (const char* str : testStrings) {
            const char* sp = shortestPalindrome(str);
            printf("Input: %-10s ==> Shortest Palindrome: \"%s\"\n",
                    "\"" + str + "\"", sp);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass for LPS computation on string of length 2N + 1.
 * Space Complexity: O(N) - Storage for mirrored string and LPS array.
 */
