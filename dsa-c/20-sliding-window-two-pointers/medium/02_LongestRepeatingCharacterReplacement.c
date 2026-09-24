/**
 * Problem: Longest Repeating Character Replacement (LeetCode 424)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * You are given a string s and an integer k. You can choose any character of the string
 * and change it to any other uppercase English character. You can perform this operation
 * at most k times. Return the length of the longest substring containing the same letter
 * you can get after performing the above operations.
 * 
 * Key Insight:
 * In a valid window [left, right], we need:
 * windowSize - maxFreq <= k
 * where maxFreq is the count of the most frequent character in the window.
 * 
 * We don't need to re-compute maxFreq when shrinking — we only expand when we find a better maxFreq.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) - only 26 characters.
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

int characterReplacement(const char* s, int k) {
        int* freq = (int*)malloc((26) * sizeof(int));
        int left = 0;
        int maxFreq = 0; // max frequency of any character in the current window
        int maxLength = 0;

        for (int right = 0; right < ((int)strlen(s)); right++) {
            freq[s[right] - 'A']++;
            maxFreq = MAX(maxFreq, freq[s[right] - 'A']);

            // If replacements needed exceed k, shrink window
            int windowSize = right - left + 1;
            if (windowSize - maxFreq > k) {
                freq[s[left++] - 'A']--;
            }

            maxLength = MAX(maxLength, right - left + 1);
        }

        return maxLength;
    }

    int main(void) {
        printf("%d (Expected: 4)\n", characterReplacement("ABAB", 2));
        // Replace both A's or both B's -> "BBBB" or "AAAA", length 4
        printf("%d (Expected: 4)\n", characterReplacement("AABABBA", 1));
        // "AABA" -> replace one B: "AAAA", length 4
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
