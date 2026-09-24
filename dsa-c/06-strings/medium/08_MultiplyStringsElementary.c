/**
 * Problem Statement:
 * Given two non-negative integers `num1` and `num2` represented as strings, return the product
 * of `num1` and `num2`, also represented as a string.
 * Must NOT use any built-in BigInteger library or convert directly to integer.
 * (LeetCode 43: Multiply Strings).
 *
 * Example:
 * num1 = "123", num2 = "456" -> "56088"
 *
 * Asked in: Facebook / Meta, Google, Microsoft, Amazon
 *
 * Approach:
 * - Grade-School Array Multiplication:
 *   Multiplying m-digit and n-digit numbers produces at most m + n digits.
 *   - Pre-allocate `int[] pos = new int[m + n]`.
 *   - Traverse indices `i` (from m-1 down to 0) and `j` (from n-1 down to 0):
 *     `mul = (num1[i] - '0') * (num2[j] - '0')`
 *     `sum = mul + pos[i + j + 1]`
 *     `pos[i + j] += sum / 10`
 *     `pos[i + j + 1] = sum % 10`
 *   - Build output string skipping leading zeros.
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
        if ("0".equals(num1) || "0".equals(num2)) return "0";

        int m = ((int)strlen(num1));
        int n = ((int)strlen(num2));
        int* pos = (int*)malloc((m + n) * sizeof(int));

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
            { "999", "999" },
            { "123456789", "987654321" }
        };

        for (const char*[] tc : testCases) {
            const char* product = multiply(tc[0], tc[1]);
            printf("%s * %s = %s\n", tc[0], tc[1], product);
        }
        return 0;
}

/*
 * Time Complexity: O(M * N) - Each digit pair is multiplied once.
 * Space Complexity: O(M + N) - Storage for product digit array.
 */
