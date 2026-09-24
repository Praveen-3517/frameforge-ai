/**
 * Problem Statement:
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 * (LeetCode 14: Longest Common Prefix).
 *
 * Example:
 * strs = ["flower","flow","flight"] -> "fl"
 * strs = ["dog","racecar","car"]    -> ""
 *
 * Asked in: Google, Apple, Amazon, Adobe
 *
 * Approach:
 * - Horizontal Scanning:
 *   Initialize `prefix = strs[0]`.
 *   Iterate through each remaining string `strs[i]`:
 *   - While `strs[i]` does not start with `prefix` (`strs[i].indexOf(prefix) != 0`):
 *     Truncate the last character from `prefix`: `prefix = prefix.substring(0, prefix.length() - 1)`.
 *     If `prefix` becomes empty, return `""` immediately!
 *   - Return `prefix`.
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

const char* longestCommonPrefix(const char*[] strs) {
        if (strs == NULL || n == 0) return "";

        const char* prefix = strs[0];

        for (int i = 1; i < n; i++) {
            while (strs[i].indexOf(prefix) != 0) {
                prefix = prefix.substring(0, ((int)strlen(prefix)) - 1);
                if (prefix.isEmpty()) {
                    return "";
                }
            }
        }

        return prefix;
    }

    int main(void) {
        printf("=== LeetCode 14: Longest Common Prefix (Horizontal Scanning) ===\n");

        const char*[][] testArrays = {
            { "flower", "flow", "flight" },
            { "dog", "racecar", "car" },
            { "interspecies", "interstellar", "interstate" },
            { "throne", "throne" }
        };

        for (const char*[] arr : testArrays) {
            const char* lcp = longestCommonPrefix(arr);
            printf("Strings: %-42s ==> Prefix: \"%s\"\n",
                    java.util."[array]", lcp);
        }
        return 0;
}

/*
 * Time Complexity: O(S) where S is the sum of all characters in all strings.
 * Space Complexity: O(1) - Constant auxiliary space.
 */
