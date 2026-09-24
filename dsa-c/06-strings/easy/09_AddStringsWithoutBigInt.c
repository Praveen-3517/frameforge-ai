/**
 * Problem Statement:
 * Given two non-negative integers `num1` and `num2` represented as string,
 * return the sum of `num1` and `num2` as a string.
 * Requirements:
 *   - You must NOT use any built-in BigInteger library.
 *   - You must NOT convert the inputs to integer directly.
 * (LeetCode 415: Add Strings).
 *
 * Example:
 * num1 = "11", num2 = "123" -> "134"
 * num1 = "456", num2 = "77"  -> "533"
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Two-Pointer Decimal Ripple-Carry Addition:
 *   Start at the least significant digits: `i = num1.length() - 1` and `j = num2.length() - 1`.
 *   Maintain `carry = 0`.
 *   While `i >= 0 || j >= 0 || carry > 0`:
 *     `int sum = carry;`
 *     If `i >= 0`: `sum += num1.charAt(i--) - '0';`
 *     If `j >= 0`: `sum += num2.charAt(j--) - '0';`
 *     Append `sum % 10` to `StringBuilder`.
 *     Update `carry = sum / 10`.
 *   Reverse the `StringBuilder` to produce the standard big-endian result.
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

const char* addStrings(const char* num1, const char* num2) {
        StringBuilder sb = new StringBuilder();
        int i = ((int)strlen(num1)) - 1;
        int j = ((int)strlen(num2)) - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += num1[i] - '0';
                i--;
            }

            if (j >= 0) {
                sum += num2[j] - '0';
                j--;
            }

            sb.append(sum % 10);
            carry = sum / 10;
        }

        return sb.reverse().toString();
    }

    int main(void) {
        printf("=== LeetCode 415: Add Large Strings (Decimal Ripple Carry) ===\n");

        const char*[][] testPairs = {
            { "11", "123" },
            { "456", "77" },
            { "0", "0" },
            { "99999999999999999999", "1" },
            { "12345678901234567890", "98765432109876543210" }
        };

        for (const char*[] pair : testPairs) {
            const char* sum = addStrings(pair[0], pair[1]);
            printf("  %s\n+ %s\n= %s\n\n", pair[0], pair[1], sum);
        }
        return 0;
}

/*
 * Time Complexity: O(max(N, M)) - Linear traversal of digits.
 * Space Complexity: O(max(N, M)) - StringBuilder for output string.
 */
