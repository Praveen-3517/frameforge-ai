/**
 * Problem Statement:
 * Given two strings `s` and `t` of lengths `m` and `n` respectively, return the minimum window substring
 * of `s` such that every character in `t` (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 * (LeetCode 76: Minimum Window Substring - Hard).
 *
 * Example:
 * s = "ADOBECODEBANC", t = "ABC" -> Output: "BANC"
 * s = "a", t = "a"               -> Output: "a"
 * s = "a", t = "aa"              -> Output: ""
 *
 * Asked in: Facebook / Meta (High Frequency), Google, Amazon, LinkedIn
 *
 * Approach:
 * - Dynamic Sliding Window with Frequency Counting (O(N) Time, O(1) Space):
 *   1. Count target character requirements in `int[] targetFreq = new int[128]`.
 *      Count how many unique characters must be matched: `required = uniqueCount`.
 *   2. Expand `right` pointer over `s`:
 *      Increment `windowFreq[s.charAt(right)]++`.
 *      If count matches requirement: `formed++`.
 *   3. While `formed == required` (all characters in t are satisfied):
 *      - Record new minimum window `[left, right]`.
 *      - Shrink window from `left`:
 *        Decrement `windowFreq[s.charAt(left)]--`.
 *        If count drops below `targetFreq[s.charAt(left)]`: `formed--`.
 *        Advance `left++`.
 *   4. Return minimum substring if found, else `""`.
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

const char* minWindow(const char* s, const char* t) {
        if (s == NULL || t == NULL || ((int)strlen(s)) < ((int)strlen(t))) return "";

        int* targetFreq = (int*)malloc((128) * sizeof(int));
        int required = 0;

        for (int i = 0; i < ((int)strlen(t)); i++) {
            char c = t[i];
            if (targetFreq[c] == 0) required++;
            targetFreq[c]++;
        }

        int* windowFreq = (int*)malloc((128) * sizeof(int));
        int formed = 0;
        int left = 0;

        int minLen = INT_MAX;
        int minStart = 0;

        for (int right = 0; right < ((int)strlen(s)); right++) {
            char c = s[right];
            windowFreq[c]++;

            if (targetFreq[c] > 0 && windowFreq[c] == targetFreq[c]) {
                formed++;
            }

            // Shrink window while all requirements are met
            while (formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }

                char leftChar = s[left];
                windowFreq[leftChar]--;
                if (targetFreq[leftChar] > 0 && windowFreq[leftChar] < targetFreq[leftChar]) {
                    formed--;
                }
                left++;
            }
        }

        return (minLen == INT_MAX) ? "" : s.substring(minStart, minStart + minLen);
    }

    int main(void) {
        printf("=== LeetCode 76: Minimum Window Substring (Sliding Window) ===\n");

        const char* s = "ADOBECODEBANC";
        const char* t = "ABC";
        const char* window = minWindow(s, t);

        printf("s: \"%s\"\nt: \"%s\"\nMinimum Window Substring: \"%s\" (Expected: \"BANC\")\n",
                s, t, window);
        return 0;
}

/*
 * Time Complexity: O(M + N) - Each character in s is visited at most twice (by left and right pointers).
 * Space Complexity: O(1) - Fixed 128-element ASCII arrays.
 */
