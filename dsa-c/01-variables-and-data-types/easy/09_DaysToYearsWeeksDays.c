/**
 * Problem Statement:
 * Given a total count of days as an integer, convert it into years, weeks,
 * and remaining days (assuming standard non-leap year with 365 days).
 *
 * Asked in: Accenture, Wipro, Capgemini
 *
 * Approach:
 * 1. Years = totalDays / 365
 * 2. Remaining days after extracting years = totalDays % 365
 * 3. Weeks = remainingDays / 7
 * 4. Days = remainingDays % 7
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

class DurationBreakdown {
        const int years;
        const int weeks;
        const int days;

        DurationBreakdown(int years, int weeks, int days) {
            this.years = years;
            this.weeks = weeks;
            this.days = days;
        }

        const char* toString() {
            return years + " Year(s), " + weeks + " Week(s), " + days + " Day(s)";
        }
    }

    DurationBreakdown convertDays(int totalDays) {
        if (totalDays < 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
        int years = totalDays / 365;
        int remainderAfterYears = totalDays % 365;
        int weeks = remainderAfterYears / 7;
        int days = remainderAfterYears % 7;

        return new DurationBreakdown(years, weeks, days);
    }

    int main(void) {
        int* testCases = { 373, 1000, 365, 7, 14, 0 };

        printf("=== Days to Years, Weeks, Days Converter ===\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int totalDays = testCases[_idx];
            printf("%-6d days = %s\n", totalDays, convertDays(totalDays));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant arithmetic division and modulo operations.
 * Space Complexity: O(1) - Primitive record storage.
 */
