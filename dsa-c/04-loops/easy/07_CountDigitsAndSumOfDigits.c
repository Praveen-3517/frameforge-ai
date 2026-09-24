/**
 * Problem Statement:
 * Given an integer `n`:
 * 1. Count the total number of digits.
 * 2. Count the frequency of even and odd digits.
 * 3. Calculate the sum of its digits.
 * 4. Compute the Digital Root (repeatedly summing digits until a single digit remains).
 *    Compare loop-based digital root against the O(1) mathematical modulo-9 formula.
 *
 * Asked in: Infosys, TCS, Wipro, Accenture, Cognizant
 *
 * Approach:
 * - Digit Processing Loop:
 *   Take absolute value `abs(n)`.
 *   Special case: if `n == 0`, digit count = 1, even count = 1, sum = 0.
 *   While `temp > 0`:
 *     `d = temp % 10;`
 *     `sum += d;`
 *     `if (d % 2 == 0) evenCount++; else oddCount++;`
 *     `temp /= 10;`
 * - Digital Root:
 *   Iterative: run digit sum loop while `num >= 10`.
 *   Formula: For positive integers, `digitalRoot = 1 + (n - 1) % 9`.
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

void analyzeDigits(long long n) {
        long long original = n;
        long long temp = abs(n);

        int totalDigits = 0;
        int evenDigits = 0;
        int oddDigits = 0;
        long long digitSum = 0;

        if (temp == 0) {
            totalDigits = 1;
            evenDigits = 1;
            digitSum = 0;
        } else {
            while (temp > 0) {
                int d = (int) (temp % 10);
                totalDigits++;
                digitSum += d;
                if ((d & 1) == 0) {
                    evenDigits++;
                } else {
                    oddDigits++;
                }
                temp /= 10;
            }
        }

        // Digital Root calculation
        long long rootLoop = abs(original);
        while (rootLoop >= 10) {
            long long subSum = 0;
            while (rootLoop > 0) {
                subSum += rootLoop % 10;
                rootLoop /= 10;
            }
            rootLoop = subSum;
        }

        // Mathematical O(1) Digital Root
        long long rootFormula = (original == 0) ? 0 : (1 + (abs(original) - 1) % 9);

        printf("---------------------------------------------------------\n");
        printf("Number        : %d\n", original);
        printf("Total Digits  : %d\n", totalDigits);
        printf("Even Digits   : %d | Odd Digits: %d\n", evenDigits, oddDigits);
        printf("Digit Sum     : %d\n", digitSum);
        printf("Digital Root  : %d (Formula O(1): %d)\n", rootLoop, rootFormula);
    }

    int main(void) {
        printf("=== Digit Analysis & Digital Root Calculation ===\n");

        long long* testNumbers = { 0, 7, 42, 12345, 9876543210L, -8493 };

        for (size_t _idx = 0; _idx < sizeof(testNumbers)/sizeof(testNumbers[0]); _idx++) {
        long long n = testNumbers[_idx];
            analyzeDigits(n);
        }
        return 0;
}

/*
 * Time Complexity: O(log10 N) - Linear scan of decimal digits.
 * Space Complexity: O(1) - Stack variables only.
 */
