/**
 * Problem Statement:
 * Given two binary strings `a` and `b`, return their sum as a binary string.
 * The strings may be up to 10,000 characters long, far exceeding standard 64-bit primitive integers.
 * (LeetCode 67: Add Binary).
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Apple, Bloomberg
 *
 * Approach:
 * - Two-Pointer Binary Ripple-Carry Addition:
 *   Start from the least significant bits (rightmost characters) and iterate backwards.
 *   Accumulate the sum of digits from `a`, `b`, and the existing `carry`.
 *   Current binary bit: `sum % 2`
 *   New carry: `sum / 2`
 *   Append each bit to a `StringBuilder` and reverse at the end.
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

const char* addBinary(const char* a, const char* b) {
        StringBuilder sb = new StringBuilder();
        int i = ((int)strlen(a)) - 1;
        int j = ((int)strlen(b)) - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += a[i] - '0';
                i--;
            }

            if (j >= 0) {
                sum += b[j] - '0';
                j--;
            }

            sb.append(sum % 2);
            carry = sum / 2;
        }

        return sb.reverse().toString();
    }

    int main(void) {
        printf("=== LeetCode 67: Arbitrary-Length Binary const char* Addition ===\n");

        const char*[][] testCases = {
            { "11", "1" },
            { "1010", "1011" },
            { "0", "0" },
            { "11111111", "1" },
            { "10000000000000000000000000000001", "11111111111111111111111111111111" }
        };

        for (const char*[] tc : testCases) {
            const char* a = tc[0];
            const char* b = tc[1];
            const char* sum = addBinary(a, b);
            printf("  %s\n+ %s\n= %s\n\n", a, b, sum);
        }
        return 0;
}

/*
 * Time Complexity: O(max(N, M)) - Linear traversal over the length of the longer binary string.
 * Space Complexity: O(max(N, M)) - Auxiliary StringBuilder to store the resulting sum string.
 */
