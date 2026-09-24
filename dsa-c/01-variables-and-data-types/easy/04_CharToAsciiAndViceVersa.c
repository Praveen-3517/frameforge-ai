/**
 * Problem Statement:
 * Given a character, find its numeric ASCII / Unicode code point.
 * Given an integer, convert it to its corresponding character.
 * Perform character classification (Uppercase, Lowercase, Digit, Special)
 * using primitive arithmetic comparisons without Character helper methods.
 *
 * Asked in: TCS, Capgemini, Wipro, Infosys
 *
 * Approach:
 * - In Java, `char` is an unsigned 16-bit integer (0 to 65535).
 * - Direct assignment of `char` to `int` gives the ASCII value.
 * - Checking character ranges:
 *     Uppercase: 'A' <= ch && ch <= 'Z' (65 to 90)
 *     Lowercase: 'a' <= ch && ch <= 'z' (97 to 122)
 *     Digit:     '0' <= ch && ch <= '9' (48 to 57)
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

int getAsciiValue(char ch) {
        return (int) ch;
    }

    char getCharFromAscii(int code) {
        return (char) code;
    }

    const char* classifyCharacter(char ch) {
        if (ch >= 'A' && ch <= 'Z') {
            return "Uppercase Letter (Shift to Lower: '" + (char)(ch + 32) + "')";
        } else if (ch >= 'a' && ch <= 'z') {
            return "Lowercase Letter (Shift to Upper: '" + (char)(ch - 32) + "')";
        } else if (ch >= '0' && ch <= '9') {
            return "Numeric Digit (int value: " + (ch - '0') + ")";
        } else {
            return "Special char / Symbol";
        }
    }

    int main(void) {
        char* testChars = { 'A', 'z', '7', '@', '₹' };

        printf("=== char & ASCII / Unicode Transformations ===\n");
        for (size_t _idx = 0; _idx < sizeof(testChars)/sizeof(testChars[0]); _idx++) {
        char ch = testChars[_idx];
            int ascii = getAsciiValue(ch);
            printf("Char: '%c' | Code: %-6d | Classification: %s\n",
                    ch, ascii, classifyCharacter(ch));
        }

        printf("\n=== Inverse Conversion (ASCII code to Char) ===\n");
        int* testCodes = { 66, 107, 53, 36 };
        for (size_t _idx = 0; _idx < sizeof(testCodes)/sizeof(testCodes[0]); _idx++) {
        int code = testCodes[_idx];
            printf("Code: %-4d -> Char: '%c'\n", code, getCharFromAscii(code));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Primitive comparison and offset arithmetic.
 * Space Complexity: O(1) - Auxiliary space.
 */
