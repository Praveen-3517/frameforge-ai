/**
 * Problem Statement:
 * Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.
 * The algorithm must:
 * 1. Ignore leading whitespace.
 * 2. Check for an optional '+' or '-' sign.
 * 3. Read subsequent digits until the next non-digit character or end of input.
 * 4. Clamp the integer if it is out of the 32-bit signed integer range:
 *    return `Integer.MIN_VALUE` if underflow, `Integer.MAX_VALUE` if overflow.
 * (LeetCode 8: String to Integer (atoi)).
 *
 * Asked in: Amazon, Microsoft, LinkedIn, Uber
 *
 * Approach:
 * - Handle empty or null strings.
 * - Skip whitespace with `while (i < n && s.charAt(i) == ' ') i++`.
 * - Read sign: check `'+'` or `'-'`.
 * - Process digits:
 *     Check overflow before multiplying: `total > Integer.MAX_VALUE / 10 || (total == Integer.MAX_VALUE / 10 && digit > 7)`.
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

int myAtoi(const char* s) {
        if (s == NULL || s.isEmpty()) return 0;

        int i = 0, n = ((int)strlen(s));
        // 1. Discard leading whitespaces
        while (i < n && s[i] == ' ') {
            i++;
        }
        if (i == n) return 0;

        // 2. Check sign
        int sign = 1;
        if (s[i] == '+' || s[i] == '-') {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        // 3. Convert digits and guard against overflow
        int total = 0;
        while (i < n) {
            char ch = s[i];
            if (ch < '0' || ch > '9') break;

            int digit = ch - '0';

            // Check overflow before updating total
            if (total > INT_MAX / 10 || (total == INT_MAX / 10 && digit > 7)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            total = total * 10 + digit;
            i++;
        }

        return total * sign;
    }

    int main(void) {
        const char*[] testInputs = {
            "42",
            "   -42",
            "4193 with words",
            "words and 987",
            "-91283472332", // Underflow -> INT_MIN (-2147483648)
            "2147483648",   // Overflow -> INT_MAX (2147483647)
            "+-12",
            ""
        };

        printf("=== LeetCode 8: Manual myAtoi Implementation ===\n");
        for (const char* input : testInputs) {
            int parsed = myAtoi(input);
            printf("Input: %-25s ==> Output: %d\n", "\"" + input + "\"", parsed);
        }
        return 0;
}

/*
 * Time Complexity: O(N) where N is the length of the string (linear single-pass scan).
 * Space Complexity: O(1) - Constant stack space.
 */
