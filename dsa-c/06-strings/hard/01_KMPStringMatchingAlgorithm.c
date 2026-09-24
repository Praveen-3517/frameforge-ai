/**
 * Problem Statement:
 * Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle`
 * in `haystack`, or -1 if `needle` is not part of `haystack`.
 * Implement the Knuth-Morris-Pratt (KMP) linear-time string matching algorithm.
 * (LeetCode 28: Find the Index of the First Occurrence in a String).
 *
 * Example:
 * haystack = "sadbutsad", needle = "sad" -> 0
 * haystack = "leetcode", needle = "leeto"  -> -1
 *
 * Asked in: Google, Microsoft, Amazon, Facebook / Meta
 *
 * Approach:
 * - Knuth-Morris-Pratt (KMP) Algorithm (O(N + M) Time, O(M) Space):
 *   Avoids the naive O(N * M) backtrack by utilizing previous match information.
 *   1. Step 1: Precompute the LPS (Longest Proper Prefix which is also Suffix) array for `needle`:
 *      `lps[i]` is the length of the longest proper prefix of `needle[0..i]` that is also a suffix of `needle[0..i]`.
 *   2. Step 2: Search `haystack` using two pointers `i` (for haystack) and `j` (for needle):
 *      - If `haystack[i] == needle[j]`: increment both `i++` and `j++`.
 *      - If `j == needle.length()`: Full match found! Return `i - j`.
 *      - If mismatch occurs (`haystack[i] != needle[j]`):
 *        - If `j != 0`: Fall back `j = lps[j - 1]` without rewinding `i`!
 *        - If `j == 0`: Increment `i++`.
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

// Precompute Longest Prefix-Suffix (LPS) Array
    int* buildLPS(const char* pattern) {
        int m = ((int)strlen(pattern));
        int* lps = (int*)malloc((m) * sizeof(int));
        int len = 0; // Length of previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // Fallback to shorter prefix
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    int strStr(const char* haystack, const char* needle) {
        if (needle == NULL || needle.isEmpty()) return 0;
        if (haystack == NULL || ((int)strlen(haystack)) < ((int)strlen(needle))) return -1;

        int n = ((int)strlen(haystack));
        int m = ((int)strlen(needle));
        int* lps = buildLPS(needle);

        int i = 0; // Pointer for haystack
        int j = 0; // Pointer for needle

        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }

            if (j == m) {
                return i - j; // Match found at index i - j
            } else if (i < n && haystack[i] != needle[j]) {
                if (j != 0) {
                    j = lps[j - 1]; // Shift needle using LPS
                } else {
                    i++;
                }
            }
        }

        return -1; // Needle not found
    }

    int main(void) {
        printf("=== Knuth-Morris-Pratt (KMP) Substring Search ===\n");

        const char* haystack1 = "ABABDABACDABABCABAB";
        const char* needle1 = "ABABCABAB";
        printf("Haystack: %s\nNeedle  : %s\nFirst Match Index: %d (Expected: 10)\n\n",
                haystack1, needle1, strStr(haystack1, needle1));

        const char* haystack2 = "sadbutsad";
        const char* needle2 = "sad";
        printf("Haystack: %s\nNeedle  : %s\nFirst Match Index: %d (Expected: 0)\n",
                haystack2, needle2, strStr(haystack2, needle2));
        return 0;
}

/*
 * Time Complexity: O(N + M) where N = haystack.length(), M = needle.length().
 * Space Complexity: O(M) - Storage for the LPS array.
 */
