/**
 * Problem: Decode Ways (LeetCode 91)
 * Asked in: Facebook, Amazon, Google, Microsoft, Uber
 * 
 * A message containing letters from A-Z can be encoded into numbers using the mapping:
 * 'A' -> "1", 'B' -> "2", ..., 'Z' -> "26".
 * Given a string s containing only digits, return the number of ways to decode it.
 * 
 * Approach:
 * 1D DP with O(1) Space Optimization:
 * At index i:
 * - Single digit: s[i-1] != '0' contributes dp[i - 1].
 * - Two digits: s[i-2..i-1] between "10" and "26" contributes dp[i - 2].
 * dp[i] = ways1 + ways2.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int numDecodings(const char* s) {
        if (s == NULL || ((int)strlen(s)) == 0 || s[0] == '0') return 0;

        int n = ((int)strlen(s));
        int prev2 = 1; // dp[0]
        int prev1 = 1; // dp[1]

        for (int i = 2; i <= n; i++) {
            int curr = 0;
            int oneDigit = s[i - 1] - '0';
            int twoDigits = int.parseInt(s.substring(i - 2, i));

            if (oneDigit >= 1 && oneDigit <= 9) {
                curr += prev1;
            }
            if (twoDigits >= 10 && twoDigits <= 26) {
                curr += prev2;
            }

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int main(void) {
        printf("Ways for '12': " + numDecodings("12") + " (Expected: 2)\n"); // "AB" or "L"
        printf("Ways for '226': " + numDecodings("226") + " (Expected: 3)\n"); // "BZ", "VF", "BBF"
        printf("Ways for '06': " + numDecodings("06") + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
