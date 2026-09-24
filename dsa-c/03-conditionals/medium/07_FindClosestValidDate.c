/**
 * Problem Statement:
 * Given a date represented by three integers `(year, month, day)`:
 * 1. Validate whether the date represents a valid Gregorian calendar date.
 * 2. If valid, compute the immediate NEXT calendar date `(year, month, day)`,
 *    handling end-of-month rollovers, leap years, and end-of-year rollovers (Dec 31 -> Jan 1).
 *
 * Asked in: Bloomberg, Goldman Sachs, TCS, Infosys
 *
 * Approach:
 * - Validity Conditionals:
 *   `year >= 1`, `1 <= month <= 12`, and `1 <= day <= maxDays(month, year)`.
 * - Month Day Capacity via Switch:
 *   31 days: 1, 3, 5, 7, 8, 10, 12
 *   30 days: 4, 6, 9, 11
 *   28/29 days: 2 (based on `isLeapYear(year)`).
 * - Next Day Rollover:
 *   - If `day < maxDays`: simply `day + 1`.
 *   - If `day == maxDays`: `day = 1`, and increment `month`.
 *     - If `month > 12`: `month = 1`, and increment `year`.
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

bool isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    int getDaysInMonth(int month, int year) {
        return switch (month) {
            case 1, 3, 5, 7, 8, 10, 12 -> 31;
            case 4, 6, 9, 11            -> 30;
            case 2                      -> isLeapYear(year) ? 29 : 28;
            default                     -> -1;
        };
    }

    bool isValidDate(int year, int month, int day) {
        if (year < 1 || month < 1 || month > 12) return false;
        int maxDays = getDaysInMonth(month, year);
        return day >= 1 && day <= maxDays;
    }

    int* getNextDate(int year, int month, int day) {
        if (!isValidDate(year, month, day)) {
            throw new IllegalArgumentException(const char*.format("Invalid Date: %04d-%02d-%02d", year, month, day));
        }

        int maxDays = getDaysInMonth(month, year);

        if (day < maxDays) {
            return (int[]){ year, month, day + 1 };
        } else {
            // End of month rollover
            if (month < 12) {
                return (int[]){ year, month + 1, 1 };
            } else {
                // End of year rollover
                return (int[]){ year + 1, 1, 1 };
            }
        }
    }

    int main(void) {
        printf("=== Gregorian Calendar Date Validator & Next-Day Rollover Engine ===\n");

        int** testDates = {
            { 2024, 2, 28 }, // Leap year -> Feb 29
            { 2023, 2, 28 }, // Non-leap year -> Mar 1
            { 2024, 2, 29 }, // Leap day -> Mar 1
            { 2024, 4, 30 }, // 30-day month -> May 1
            { 2024, 12, 31 },// New Year rollover -> 2025-01-01
            { 2024, 2, 30 }  // Invalid date
        };

        for (int* d : testDates) {
            int y = d[0], m = d[1], day = d[2];
            bool valid = isValidDate(y, m, day);
            printf("Date: %04d-%02d-%02d | Valid: %-5s", y, m, day, valid);
            if (valid) {
                int* next = getNextDate(y, m, day);
                printf(" | Next Day: %04d-%02d-%02d\n", next[0], next[1], next[2]);
            } else {
                printf("\n");
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant branch evaluations and boundary checks.
 * Space Complexity: O(1) - Stack variables only.
 */
