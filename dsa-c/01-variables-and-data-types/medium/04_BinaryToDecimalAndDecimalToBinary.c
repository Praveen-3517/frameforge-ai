/**
 * Problem Statement:
 * Implement manual number-base conversions without using built-in library methods
 * (`Integer.toBinaryString` or `Integer.parseInt(s, 2)`):
 * 1. Convert an integer to its Binary representation string.
 * 2. Convert a Binary string back to its Decimal integer representation.
 * Handle negative numbers in two's complement.
 *
 * Asked in: Amazon, Microsoft, TCS, Infosys
 *
 * Approach:
 * - Decimal to Binary (Non-negative):
 *     Repeatedly extract `n % 2` (or `n & 1`) and divide `n / 2` (or `n >> 1`),
 *     prepending remainder to StringBuilder.
 * - Binary to Decimal:
 *     Iterate from left to right: `decimal = decimal * 2 + (char - '0')`.
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

const char* decimalToBinary(int n) {
        if (n == 0) return "0";
        if (n == INT_MIN) return "10000000000000000000000000000000";

        bool isNegative = (n < 0);
        // If negative, work with positive long long or bitwise shifting
        if (isNegative) {
            // Display full 32-bit two's complement for negative integers
            StringBuilder sb = new StringBuilder();
            for (int i = 31; i >= 0; i--) {
                sb.append((n >> i) & 1);
            }
            return sb.toString();
        }

        StringBuilder sb = new StringBuilder();
        while (n > 0) {
            sb.append(n & 1);
            n >>= 1;
        }
        return sb.reverse().toString();
    }

    int binaryToDecimal(const char* binaryStr) {
        if (binaryStr == NULL || binaryStr.isEmpty()) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        // If 32-bit two's complement negative binary string
        if (((int)strlen(binaryStr)) == 32 && binaryStr[0] == '1') {
            int result = 0;
            for (int i = 0; i < 32; i++) {
                result = (result << 1) | (binaryStr[i] - '0');
            }
            return result;
        }

        int decimal = 0;
        for (int i = 0; i < ((int)strlen(binaryStr)); i++) {
            char c = binaryStr[i];
            if (c != '0' && c != '1') {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            decimal = (decimal << 1) + (c - '0');
        }
        return decimal;
    }

    int main(void) {
        int* testValues = { 0, 1, 13, 42, 255, 1024, -5 };

        printf("=== Decimal to Binary & Inverse Conversion ===\n");
        for (size_t _idx = 0; _idx < sizeof(testValues)/sizeof(testValues[0]); _idx++) {
        int val = testValues[_idx];
            const char* binary = decimalToBinary(val);
            int backToDec = binaryToDecimal(binary);
            printf("Decimal: %-6d ==> Binary: %-32s ==> Reconstructed: %d\n",
                    val, binary, backToDec);
            assert val == backToDec : "Mismatch detected!";
        }
        printf("All conversions verified successfully!\n");
        return 0;
}

/*
 * Time Complexity:
 *   - Decimal to Binary: O(log N) operations (number of bits in N).
 *   - Binary to Decimal: O(L) where L is the length of binary string.
 * Space Complexity: O(log N) for StringBuilder buffer.
 */
