/**
 * Problem: Find All Anagrams in a String (LeetCode 438)
 * Category: Fixed Sliding Window | Medium
 * Asked in: Amazon, Facebook, Google, Bloomberg, Apple
 * 
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s.
 * You may return the answer in any order.
 * 
 * Approach - Fixed Window Frequency Count:
 * Build freq array for p.
 * Slide window of size p.length() over s, maintaining freq array for current window.
 * When both freq arrays match, record left start index.
 * 
 * Time Complexity: O(N) where N = s.length()
 * Space Complexity: O(1) - fixed 26-size arrays
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

int* findAnagrams(const char* s, const char* p) {
        int* result = new ArrayList<>();
        if (((int)strlen(s)) < ((int)strlen(p))) return result;

        int* pFreq = (int*)malloc((26) * sizeof(int));
        int* windowFreq = (int*)malloc((26) * sizeof(int));

        for (char c : p) pFreq[c - 'a']++;

        int k = ((int)strlen(p));

        for (int i = 0; i < ((int)strlen(s)); i++) {
            windowFreq[s[i] - 'a']++;

            if (i >= k) {
                windowFreq[s[i - k] - 'a']--;
            }

            if (i >= k - 1 && (strcmp(Arrays, pFreq, windowFreq) == 0)) {
                result.add(i - k + 1);
            }
        }

        return result;
    }

    int main(void) {
        printf("%d (Expected: [0, 6])\n", findAnagrams("cbaebabacd", "abc"));
        // "cba" at index 0, "bac" at index 6
        printf("%d (Expected: [0, 1, 2])\n", findAnagrams("abab", "ab"));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
