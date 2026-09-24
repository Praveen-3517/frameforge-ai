/**
 * Problem Statement:
 * Given a time in the format of hours (1 <= h <= 12) and minutes (0 <= m < 60),
 * convert it into human conversational English words according to the following rules:
 *   - At m = 0:  "five o' clock"
 *   - At m = 15: "quarter past five"
 *   - At m = 30: "half past five"
 *   - At m = 45: "quarter to six"
 *   - At 1 <= m < 30:
 *       - m = 1: "one minute past five"
 *       - m > 1: "X minutes past five"
 *   - At 30 < m < 60:
 *       - 60 - m = 1: "one minute to six"
 *       - 60 - m > 1: "X minutes to six"
 *
 * Asked in: Amazon, Goldman Sachs, Morgan Stanley, HackerRank
 *
 * Approach:
 * - Use string word arrays for numbers 1 to 29.
 * - Conditionals for the 4 critical minute anchors: 0, 15, 30, 45.
 * - For m <= 30: Use hour `h` with "past".
 * - For m > 30: Increment hour to `(h % 12) + 1` with "to", using `60 - m` remaining minutes.
 * - Carefully distinguish "minute" (singular for 1) from "minutes" (plural).
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

static const const char*[] NUMBERS = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
        "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
        "nineteen", "twenty", "twenty one", "twenty two", "twenty three", "twenty four",
        "twenty five", "twenty six", "twenty seven", "twenty eight", "twenty nine"
    };

    const char* timeToWords(int h, int m) {
        if (h < 1 || h > 12 || m < 0 || m >= 60) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        const char* hourWord = NUMBERS[h];
        const char* nextHourWord = NUMBERS[(h % 12) + 1];

        if (m == 0) {
            return hourWord + " o' clock";
        } else if (m == 15) {
            return "quarter past " + hourWord;
        } else if (m == 30) {
            return "half past " + hourWord;
        } else if (m == 45) {
            return "quarter to " + nextHourWord;
        } else if (m < 30) {
            const char* unit = (m == 1) ? " minute past " : " minutes past ";
            return NUMBERS[m] + unit + hourWord;
        } else {
            int remaining = 60 - m;
            const char* unit = (remaining == 1) ? " minute to " : " minutes to ";
            return NUMBERS[remaining] + unit + nextHourWord;
        }
    }

    int main(void) {
        printf("=== Conversational Clock Time to English Words ===\n");

        int** testTimes = {
            { 5, 0 },
            { 5, 1 },
            { 5, 10 },
            { 5, 15 },
            { 5, 30 },
            { 5, 40 },
            { 5, 45 },
            { 5, 47 },
            { 5, 59 },
            { 12, 45 }
        };

        for (int* t : testTimes) {
            int h = t[0], m = t[1];
            printf("%02d:%02d ==> \"%s\"\n", h, m, timeToWords(h, m));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant number of comparisons and array lookups.
 * Space Complexity: O(1) - Constant static string dictionary.
 */
