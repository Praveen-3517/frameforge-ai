/**
 * Problem: Longest Substring Without Repeating Characters (LeetCode 3)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Bloomberg, Google, Apple, Microsoft, Facebook
 * 
 * Given a string s, find the length of the longest substring without repeating characters.
 * 
 * Approach - Variable Window + HashSet:
 * Maintain a sliding window [left, right] with no duplicates using a HashSet.
 * Expand right. If s[right] already in set, shrink from left until it's gone.
 * Track max window size.
 * 
 * Time Complexity: O(N) - each character enters and leaves the window at most once.
 * Space Complexity: O(min(N, charset_size))
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
        Set<char> window = new HashSet<>();
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < ((int)strlen(s)); right++) {
            char c = s[right];

            while (window.contains(c)) {
                window.remove(s[left++]);
            }

            window.add(c);
            maxLength = MAX(maxLength, right - left + 1);
        }

        return maxLength;
    }

    int main(void) {
        printf("%d (Expected: 3)\n", lengthOfLongestSubstring("abcabcbb")); // "abc"
        printf("%d (Expected: 1)\n", lengthOfLongestSubstring("bbbbb"));    // "b"
        printf("%d (Expected: 3)\n", lengthOfLongestSubstring("pwwkew"));   // "wke"
        printf("%d (Expected: 0)\n", lengthOfLongestSubstring(""));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
