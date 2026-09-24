/**
 * Problem Statement:
 * Given two version strings, `version1` and `version2`, compare them.
 * A version number consists of one or more revisions joined by a dot '.'.
 * Each revision consists of digits and may contain leading zeros.
 * Return:
 *   - -1 if version1 < version2
 *   -  1 if version1 > version2
 *   -  0 if version1 == version2
 * Treat missing revisions as 0 (e.g., "1.0" and "1.0.0" are equal).
 * (LeetCode 165: Compare Version Numbers).
 *
 * Example:
 * version1 = "1.2",   version2 = "1.10"   -> -1
 * version1 = "1.01",  version2 = "1.001"  -> 0
 * version1 = "1.0",   version2 = "1.0.0.0" -> 0
 *
 * Asked in: Apple, Microsoft, Amazon, Google
 *
 * Approach:
 * - Two-Pointer Zero-Allocation Parsing (O(max(N, M)) Time, O(1) Space):
 *   Instead of calling `s.split("\\.")` (which creates array and String allocations),
 *   use two pointers `i` and `j`:
 *   - For each revision chunk:
 *     Parse `num1` by reading digits until '.' or string end.
 *     Parse `num2` by reading digits until '.' or string end.
 *     If `num1 < num2`: return -1.
 *     If `num1 > num2`: return 1.
 *     Skip '.' and continue.
 *   - Missing trailing revisions automatically default to 0.
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

int compareVersion(const char* version1, const char* version2) {
        int n1 = ((int)strlen(version1));
        int n2 = ((int)strlen(version2));
        int i = 0, j = 0;

        while (i < n1 || j < n2) {
            int num1 = 0;
            while (i < n1 && version1[i] != '.') {
                num1 = num1 * 10 + (version1[i] - '0');
                i++;
            }

            int num2 = 0;
            while (j < n2 && version2[j] != '.') {
                num2 = num2 * 10 + (version2[j] - '0');
                j++;
            }

            if (num1 < num2) return -1;
            if (num1 > num2) return 1;

            // Skip the '.'
            i++;
            j++;
        }

        return 0;
    }

    int main(void) {
        printf("=== LeetCode 165: Compare Version Numbers (Two Pointers) ===\n");

        const char*[][] versionPairs = {
            { "1.2", "1.10" },
            { "1.01", "1.001" },
            { "1.0", "1.0.0.0" },
            { "0.1", "1.1" },
            { "7.5.2.4", "7.5.3" }
        };

        for (const char*[] pair : versionPairs) {
            int result = compareVersion(pair[0], pair[1]);
            const char* cmp = (result == -1) ? "<" : (result == 1 ? ">" : "==");
            printf("\"%s\" %s \"%s\" (Code: %d)\n", pair[0], cmp, pair[1], result);
        }
        return 0;
}

/*
 * Time Complexity: O(max(N, M)) - Linear scan of both version strings.
 * Space Complexity: O(1) - Pointer variables only. Zero heap allocations.
 */
