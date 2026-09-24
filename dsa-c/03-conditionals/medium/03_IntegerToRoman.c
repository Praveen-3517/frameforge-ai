/**
 * Problem Statement:
 * Given an integer `num` (in range 1 to 3999), convert it to a Roman numeral.
 * (LeetCode 12: Integer to Roman).
 *
 * Example:
 * 3749 -> "MMMDCCXLIX"
 * 58   -> "LVIII"
 * 1994 -> "MCMXCIV"
 *
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 *
 * Approach:
 * - Greedy Value-Symbol Boundaries:
 *   Roman numerals use 13 fixed milestone values:
 *   1000 ("M"), 900 ("CM"), 500 ("D"), 400 ("CD"),
 *   100  ("C"),  90 ("XC"),  50 ("L"),  40 ("XL"),
 *   10   ("X"),   9 ("IX"),   5 ("V"),   4 ("IV"),
 *   1    ("I").
 * - Starting from the largest value (1000), greedily subtract the value while `num >= values[i]`,
 *   appending the corresponding Roman symbol to a `StringBuilder`.
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

static const int* VALUES = {
        1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };

    static const const char*[] SYMBOLS = {
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };

    const char* intToRoman(int num) {
        if (num < 1 || num > 3999) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < n && num > 0; i++) {
            while (num >= VALUES[i]) {
                sb.append(SYMBOLS[i]);
                num -= VALUES[i];
            }
        }

        return sb.toString();
    }

    int main(void) {
        printf("=== LeetCode 12: int to Roman Numeral Converter ===\n");

        int* testNumbers = { 3, 4, 9, 58, 1994, 2024, 3749, 3999 };

        for (size_t _idx = 0; _idx < sizeof(testNumbers)/sizeof(testNumbers[0]); _idx++) {
        int num = testNumbers[_idx];
            printf("int: %4d ==> Roman: %s\n", num, intToRoman(num));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - The loop runs through 13 constants, and num is bounded by 3999.
 * Space Complexity: O(1) - StringBuilder with at most 15 characters.
 */
