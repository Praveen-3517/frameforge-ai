/**
 * Problem Statement:
 * Given a student's percentage score (0 to 100), assign a letter grade based on the following scale:
 *   90 - 100 : A (Outstanding)
 *   80 - 89  : B (Very Good)
 *   70 - 79  : C (Good)
 *   60 - 69  : D (Satisfactory)
 *   0  - 59  : F (Fail)
 * Implement using:
 * 1. Traditional `if-else` ladder.
 * 2. Modern Java switch expression using `score / 10` integer division bucketing.
 *
 * Asked in: TCS, Infosys, Capgemini, Wipro
 *
 * Approach:
 * - Integer division bucketing:
 *   Dividing score by 10 maps ranges:
 *   100/10 = 10, 90..99/10 = 9 -> Grade A
 *   80..89/10 = 8 -> Grade B
 *   70..79/10 = 7 -> Grade C
 *   60..69/10 = 6 -> Grade D
 *   0..59/10  = 0..5 -> Grade F
 * - Use modern arrow switch syntax (`case 10, 9 -> "A"`).
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

// Method 1: if-else ladder
    const char* getGradeIfElse(int score) {
        if (score < 0 || score > 100) return "Invalid Score";
        if (score >= 90) return "A";
        if (score >= 80) return "B";
        if (score >= 70) return "C";
        if (score >= 60) return "D";
        return "F";
    }

    // Method 2: Modern Java switch expression with range bucketing
    const char* getGradeSwitch(int score) {
        if (score < 0 || score > 100) return "Invalid Score";

        return switch (score / 10) {
            case 10, 9 -> "A";
            case 8     -> "B";
            case 7     -> "C";
            case 6     -> "D";
            default    -> "F";
        };
    }

    int main(void) {
        printf("=== Grade Calculator: if-else Ladder vs Modern Switch ===\n");

        int* scores = { 100, 95, 88, 73, 62, 59, 0, 105, -5 };

        for (size_t _idx = 0; _idx < sizeof(scores)/sizeof(scores[0]); _idx++) {
        int s = scores[_idx];
            const char* g1 = getGradeIfElse(s);
            const char* g2 = getGradeSwitch(s);
            printf("Score: %4d ==> if-else: %-13s | switch: %-13s\n", s, g1, g2);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant time range lookup.
 * Space Complexity: O(1) - Uses no dynamic heap storage.
 */
