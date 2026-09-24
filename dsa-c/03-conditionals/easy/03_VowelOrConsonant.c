/**
 * Problem Statement:
 * Given a single character, determine whether it is a:
 * 1. Vowel (A, E, I, O, U, case-insensitive)
 * 2. Consonant
 * 3. Non-alphabetic character (digit, punctuation, symbol)
 * Demonstrate using both traditional `switch` with intentional fall-through and modern switch expressions.
 *
 * Asked in: TCS, Infosys, Accenture, Cognizant
 *
 * Approach:
 * - Character normalization: Convert input character to lowercase using `Character.toLowerCase(ch)`.
 * - First check if character is alphabetic using `Character.isLetter(ch)`.
 * - Switch fall-through:
 *   In traditional switch:
 *   `case 'a': case 'e': case 'i': case 'o': case 'u': return "Vowel";`
 * - In modern switch:
 *   `case 'a', 'e', 'i', 'o', 'u' -> "Vowel";`
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

const char* classifyChar(char ch) {
        if (!isalpha(ch)) {
            return "Non-Alphabetic Symbol";
        }

        char lower = tolower(ch);

        return switch (lower) {
            case 'a', 'e', 'i', 'o', 'u' -> "Vowel";
            default -> "Consonant";
        };
    }

    int main(void) {
        printf("=== char Classification: Vowel, Consonant, or Symbol ===\n");

        char* testChars = { 'a', 'E', 'z', 'M', '7', '@', ' ', 'u', 'Y' };

        for (size_t _idx = 0; _idx < sizeof(testChars)/sizeof(testChars[0]); _idx++) {
        char ch = testChars[_idx];
            printf("Char: '%c' ==> %s\n", ch, classifyChar(ch));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Single character lookup.
 * Space Complexity: O(1) - Constant stack registers.
 */
