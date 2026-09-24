/**
 * Problem Statement:
 * 1. Compute the sum of digits of an integer `n` recursively.
 * 2. Compute the recursive Digital Root (repeatedly summing digits until a single digit remains).
 *
 * Example:
 * n = 9875 -> Sum = 9 + 8 + 7 + 5 = 29 -> Digital Root = 2 + 9 = 11 -> 1 + 1 = 2
 *
 * Asked in: Infosys, Capgemini, TCS, Wipro
 *
 * Approach:
 * - Recursive Sum of Digits:
 *   Base Case: If `n == 0`, return 0.
 *   Recursive Step: `(n % 10) + sumOfDigits(n / 10)`.
 * - Recursive Digital Root:
 *   Base Case: If `n < 10`, return `n`.
 *   Recursive Step: `digitalRoot(sumOfDigits(n))`.
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

int sumOfDigits(int n) {
        n = abs(n);
        if (n == 0) return 0;
        return (n % 10) + sumOfDigits(n / 10);
    }

    int digitalRoot(int n) {
        n = abs(n);
        if (n < 10) return n;
        return digitalRoot(sumOfDigits(n));
    }

    int main(void) {
        printf("=== Recursive Sum of Digits & Digital Root ===\n");

        int* testNumbers = { 0, 7, 1234, 9875, 999999, -456 };

        for (size_t _idx = 0; _idx < sizeof(testNumbers)/sizeof(testNumbers[0]); _idx++) {
        int num = testNumbers[_idx];
            int sum = sumOfDigits(num);
            int root = digitalRoot(num);
            printf("Number: %7d ==> Digit Sum: %2d | Digital Root: %d\n",
                    num, sum, root);
        }
        return 0;
}

/*
 * Time Complexity: O(log10 N) - One recursive call per digit.
 * Space Complexity: O(log10 N) - Stack frames bounded by the number of decimal digits.
 */
