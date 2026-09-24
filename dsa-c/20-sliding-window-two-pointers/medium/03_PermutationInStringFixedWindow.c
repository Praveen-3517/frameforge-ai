/**
 * Problem: Permutation in String (LeetCode 567)
 * Category: Fixed Sliding Window | Medium
 * Asked in: Amazon, Google, Apple, Bloomberg, Microsoft
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1,
 * or false otherwise. In other words, return true if one of s1's permutations
 * is a substring of s2.
 * 
 * Approach - Fixed Window Frequency Matching:
 * Maintain a frequency map for s1 and a sliding window of size s1.length() over s2.
 * At each step, compare the two frequency arrays.
 * Arrays.equals() in O(26) = O(1) time.
 * 
 * Time Complexity: O(N) where N = s2.length()
 * Space Complexity: O(1) - fixed size of 26.
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

bool checkInclusion(const char* s1, const char* s2) {
        if (((int)strlen(s1)) > ((int)strlen(s2))) return false;

        int* s1Freq = (int*)malloc((26) * sizeof(int));
        int* windowFreq = (int*)malloc((26) * sizeof(int));

        for (char c : s1) s1Freq[c - 'a']++;

        int k = ((int)strlen(s1));

        for (int i = 0; i < ((int)strlen(s2)); i++) {
            windowFreq[s2[i] - 'a']++;

            if (i >= k) {
                windowFreq[s2[i - k] - 'a']--;
            }

            if (i >= k - 1 && (strcmp(Arrays, s1Freq, windowFreq) == 0)) {
                return true;
            }
        }

        return false;
    }

    int main(void) {
        printf("%d (Expected: true)\n", checkInclusion("ab", "eidbaooo"));  // "ba" is perm of "ab"
        printf("%d (Expected: false)\n", checkInclusion("ab", "eidboaoo"));
        printf("%d (Expected: true)\n", checkInclusion("adc", "dcda"));     // "dca" or "cda"
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
