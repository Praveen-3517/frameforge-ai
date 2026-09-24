/**
 * Problem Statement:
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D, and M.
 * Given a roman numeral string `s`, convert it to an integer.
 * (LeetCode 13: Roman to Integer).
 *
 * Symbol Values:
 * I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
 * Subtractive instances:
 * - I before V (4) or X (9)
 * - X before L (40) or C (90)
 * - C before D (400) or M (900)
 *
 * Asked in: Amazon, Google, Microsoft, Adobe, Apple
 *
 * Approach:
 * - Traverse the Roman string from left to right:
 *   Compare value of current character with the value of the next character:
 *   - If `currentVal < nextVal`: A subtractive pair is present (e.g. IV = 4, IX = 9).
 *     Subtract `currentVal` from accumulator.
 *   - Else: Add `currentVal` to accumulator.
 * - Use modern switch expression for character-to-value translation.
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

static int charValue(char ch) {
        return switch (ch) {
            case 'I' -> 1;
            case 'V' -> 5;
            case 'X' -> 10;
            case 'L' -> 50;
            case 'C' -> 100;
            case 'D' -> 500;
            case 'M' -> 1000;
            default  -> fprintf(stderr, "Exception: invalid argument
"); return 0;
        };
    }

    int romanToInt(const char* s) {
        int total = 0;
        int n = ((int)strlen(s));

        for (int i = 0; i < n; i++) {
            int current = charValue(s[i]);

            // Check if subtractive condition applies
            if (i + 1 < n && current < charValue(s[i + 1])) {
                total -= current;
            } else {
                total += current;
            }
        }

        return total;
    }

    int main(void) {
        printf("=== LeetCode 13: Roman to int (Switch Conditionals) ===\n");

        const char*[] testNumerals = { "III", "LVIII", "MCMXCIV", "IX", "XL", "CDXLIV", "MMXXIV" };

        for (const char* rom : testNumerals) {
            printf("Roman: %-10s ==> int: %d\n", rom, romanToInt(rom));
        }
        return 0;
}

/*
 * Time Complexity: O(N) where N is string length (N <= 15 for standard Roman numerals).
 * Space Complexity: O(1) - Constant stack storage.
 */
