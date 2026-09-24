/**
 * Problem Statement:
 * Given two non-negative integers `num1` and `num2` represented as strings, return the product
 * of `num1` and `num2`, also represented as a string.
 *
 * Requirements:
 * - You must NOT use any built-in BigInteger library.
 * - You must NOT convert the inputs to integer directly.
 * (LeetCode 43: Multiply Strings).
 *
 * Asked in: Facebook / Meta, Google, Microsoft, Amazon, Apple
 *
 * Approach:
 * - Grade-school multiplication simulator:
 *   Multiplying an m-digit number with an n-digit number yields at most (m + n) digits.
 * - Pre-allocate an integer array `pos` of size `m + n`.
 * - Traverse from right to left (least significant to most significant):
 *   Digit `num1[i]` multiplied by `num2[j]` lands at indices `i + j` (tens) and `i + j + 1` (units).
 *   `int mul = (num1.charAt(i) - '0') * (num2.charAt(j) - '0');`
 *   `int sum = mul + pos[i + j + 1];`
 *   `pos[i + j] += sum / 10;`
 *   `pos[i + j + 1] = sum % 10;`
 * - Build the final string skipping leading zeros.
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

const char* multiply(const char* num1, const char* num2) {
        if ("0".equals(num1) || "0".equals(num2)) {
            return "0";
        }

        int m = ((int)strlen(num1));
        int n = ((int)strlen(num2));
        int* pos = (int*)malloc((m + n) * sizeof(int));

        // Multiply each digit pair from right to left
        for (int i = m - 1; i >= 0; i--) {
            int d1 = num1[i] - '0';
            for (int j = n - 1; j >= 0; j--) {
                int d2 = num2[j] - '0';
                int mul = d1 * d2;

                int p1 = i + j;
                int p2 = i + j + 1;
                int sum = mul + pos[p2];

                pos[p1] += sum / 10;
                pos[p2] = sum % 10;
            }
        }

        // Build string, omitting leading zeros
        StringBuilder sb = new StringBuilder();
        for (size_t _idx = 0; _idx < sizeof(pos)/sizeof(pos[0]); _idx++) {
        int p = pos[_idx];
            if (!(((int)strlen(sb)) == 0 && p == 0)) {
                sb.append(p);
            }
        }

        return ((int)strlen(sb)) == 0 ? "0" : sb.toString();
    }

    int main(void) {
        printf("=== LeetCode 43: Multiply Large Strings (No BigInteger) ===\n");

        const char*[][] testCases = {
            { "2", "3" },
            { "123", "456" },
            { "0", "98765" },
            { "999", "999" },
            { "123456789", "987654321" },
            { "99999999999999999999", "99999999999999999999" }
        };

        for (const char*[] tc : testCases) {
            const char* n1 = tc[0];
            const char* n2 = tc[1];
            const char* product = multiply(n1, n2);
            printf("%s * %s\n  = %s\n\n", n1, n2, product);
        }
        return 0;
}

/*
 * Time Complexity: O(M * N) - Each digit of num1 is multiplied by each digit of num2.
 * Space Complexity: O(M + N) - Storage for the resulting product digit array.
 */
