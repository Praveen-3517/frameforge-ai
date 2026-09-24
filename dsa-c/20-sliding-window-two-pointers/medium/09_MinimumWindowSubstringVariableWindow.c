/**
 * Problem: Minimum Window Substring (LeetCode 76)
 * Category: Variable Sliding Window | Medium/Hard
 * Asked in: Amazon, Facebook, Google, Apple, Bloomberg, Microsoft
 * 
 * Given two strings s and t of lengths m and n respectively, return the minimum window
 * substring of s such that every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 * 
 * Approach - Variable Window with Need/Have Counter:
 * `need`: number of distinct characters in t that still need to be satisfied.
 * `windowFreq`: frequency of characters in current window.
 * Expand: include s[right]. If windowFreq[c] == tFreq[c], one need satisfied.
 * Once need == 0: record window size; shrink from left.
 *   When shrinking removes a needed char (windowFreq[c] < tFreq[c]), increment need.
 * 
 * Time Complexity: O(N + M) where N = s.length, M = t.length
 * Space Complexity: O(M) for frequency maps.
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
        Map<char, int> tFreq = new HashMap<>();
        for (size_t _idx = 0; _idx < sizeof(t)/sizeof(t[0]); _idx++) {
        char c = t[_idx];
            tFreq.merge(c, 1, int::sum);
        }

        int need = tFreq.size(); // number of unique chars in t yet to be satisfied
        int left = 0;
        int minStart = 0;
        int minLength = INT_MAX;
        Map<char, int> windowFreq = new HashMap<>();

        for (int right = 0; right < ((int)strlen(s)); right++) {
            char c = s[right];
            windowFreq.merge(c, 1, int::sum);

            if (tFreq.containsKey(c) && windowFreq.get(c).equals(tFreq.get(c))) {
                need--;
            }

            while (need == 0) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minStart = left;
                }

                char leftChar = s[left++];
                windowFreq.merge(leftChar, -1, int::sum);

                if (tFreq.containsKey(leftChar) && windowFreq.get(leftChar) < tFreq.get(leftChar)) {
                    need++;
                }
            }
        }

        return minLength == INT_MAX ? "" : s.substring(minStart, minStart + minLength);
    }

    int main(void) {
        printf("%d (Expected: BANC)\n", minWindow("ADOBECODEBANC", "ABC"));
        printf("%d (Expected: a)\n", minWindow("a", "a"));
        printf("%d (Expected: empty string)\n", minWindow("a", "aa"));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
