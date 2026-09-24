/**
 * Problem Statement:
 * Given a string `s`, find the length of the longest substring without repeating characters.
 * (LeetCode 3: Longest Substring Without Repeating Characters).
 *
 * Example:
 * s = "abcabcbb" -> 3 ("abc")
 * s = "bbbbb"    -> 1 ("b")
 * s = "pwwkew"   -> 3 ("wke")
 *
 * Asked in: Amazon, Microsoft, Google, Facebook / Meta, Bloomberg (Top 3 Most Asked)
 *
 * Approach:
 * - Optimized Sliding Window with Last-Seen Index Map:
 *   Maintain `left` pointer of window and `maxLen`.
 *   - For each character at index `right`:
 *     If `s[right]` was seen previously at `prevIdx >= left`:
 *       Jump `left = prevIdx + 1` directly, bypassing all redundant sub-windows!
 *     Record character position: `map.put(s.charAt(right), right)`.
 *     Update `maxLen = Math.max(maxLen, right - left + 1)`.
 * - Time: O(N), Space: O(min(N, AlphabetSize)).
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

int lengthOfLongestSubstring(const char* s) {
        if (s == NULL || s.isEmpty()) return 0;

        // Map character -> last seen index
        Map<char, int> lastSeen = new HashMap<>();
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < ((int)strlen(s)); right++) {
            char ch = s[right];

            if (lastSeen.containsKey(ch)) {
                // Advance left pointer to the right of the duplicate character
                left = MAX(left, lastSeen.get(ch) + 1);
            }

            lastSeen.put(ch, right);
            maxLen = MAX(maxLen, right - left + 1);
        }

        return maxLen;
    }

    int main(void) {
        printf("=== LeetCode 3: Longest Substring Without Repeating Characters ===\n");

        const char*[] testCases = { "abcabcbb", "bbbbb", "pwwkew", "", "dvdf", "abba" };

        for (const char* str : testCases) {
            int len = lengthOfLongestSubstring(str);
            printf("const char*: %-12s ==> Max Unique Substring Length: %d\n",
                    "\"" + str + "\"", len);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Right pointer scans each character once.
 * Space Complexity: O(min(N, Sigma)) - Map stores unique characters in current window.
 */
