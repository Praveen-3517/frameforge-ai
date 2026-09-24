/**
 * Problem Statement:
 * Given a string `s` consisting of words and spaces, return the length of the last word in the string.
 * A word is a maximal substring consisting of non-space characters only.
 * (LeetCode 58: Length of Last Word).
 *
 * Example:
 * s = "Hello World"                 -> 5
 * s = "   fly me   to   the moon  " -> 4
 * s = "luffy is still joyboy"       -> 6
 *
 * Asked in: Apple, Adobe, Amazon, Cisco
 *
 * Approach:
 * - Backward Traversal (O(N) Worst Case, O(1) Space):
 *   1. Start from the end of the string `i = s.length() - 1`.
 *   2. Decrement `i` to skip any trailing whitespace: `while (i >= 0 && s.charAt(i) == ' ') i--;`
 *   3. Count non-whitespace characters until the next space or start of string is reached:
 *      `while (i >= 0 && s.charAt(i) != ' ') { length++; i--; }`
 *   4. Return `length`.
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

int lengthOfLastWord(const char* s) {
        if (s == NULL || s.isEmpty()) return 0;

        int i = ((int)strlen(s)) - 1;
        int length = 0;

        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        // Count characters of the last word
        while (i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }

        return length;
    }

    int main(void) {
        printf("=== LeetCode 58: Length of Last Word (Backward Scan) ===\n");

        const char*[] testStrings = {
            "Hello World",
            "   fly me   to   the moon  ",
            "luffy is still joyboy",
            "a",
            "    day    "
        };

        for (const char* str : testStrings) {
            printf("const char*: %-30s ==> Last Word Length: %d\n",
                    "\"" + str + "\"", lengthOfLastWord(str));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Backward scan stops as soon as the last word is counted.
 * Space Complexity: O(1) - Constant stack registers.
 */
