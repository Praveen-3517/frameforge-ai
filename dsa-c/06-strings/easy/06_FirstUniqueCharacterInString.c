/**
 * Problem Statement:
 * Given a string `s`, find the first non-repeating character in it and return its index.
 * If it does not exist, return -1.
 * (LeetCode 387: First Unique Character in a String).
 *
 * Example:
 * s = "leetcode"     -> Output: 0 (character 'l')
 * s = "loveleetcode" -> Output: 2 (character 'v')
 * s = "aabb"         -> Output: -1
 *
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Google
 *
 * Approach:
 * - Two-Pass Frequency Array (O(N) Time, O(1) Space):
 *   1. Pass 1: Count frequency of each character in a 26-element array `freq[c - 'a']++`.
 *   2. Pass 2: Iterate through the string from left to right.
 *      Return the first index `i` where `freq[s.charAt(i) - 'a'] == 1`.
 *   3. If no character has frequency 1, return -1.
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

int firstUniqChar(const char* s) {
        if (s == NULL || s.isEmpty()) return -1;

        int* freq = (int*)malloc((26) * sizeof(int));

        // Pass 1: Build frequency map
        for (int i = 0; i < ((int)strlen(s)); i++) {
            freq[s[i] - 'a']++;
        }

        // Pass 2: Find first character with count 1
        for (int i = 0; i < ((int)strlen(s)); i++) {
            if (freq[s[i] - 'a'] == 1) {
                return i;
            }
        }

        return -1;
    }

    int main(void) {
        printf("=== LeetCode 387: First Unique char in a const char* ===\n");

        const char*[] testStrings = { "leetcode", "loveleetcode", "aabb", "z", "racecar" };

        for (const char* str : testStrings) {
            int idx = firstUniqChar(str);
            printf("const char*: %-15s ==> Index: %2d (Char: %s)\n",
                    "\"" + str + "\"", idx, (idx != -1 ? "'" + str[idx] + "'" : "None"));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Two passes through the string.
 * Space Complexity: O(1) - Fixed 26-element frequency bucket.
 */
