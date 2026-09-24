/**
 * Problem Statement:
 * Given two 32-bit integers `a` and `b`, detect whether their addition `a + b`
 * or multiplication `a * b` will result in an arithmetic overflow, BEFORE performing the operation.
 * Compare manual condition checks with Java 8's `Math.addExact` / `Math.multiplyExact`.
 *
 * Asked in: Google, Microsoft, Bloomberg
 *
 * Approach:
 * Addition Overflow Conditions:
 *   If b > 0 and a > Integer.MAX_VALUE - b  --> Overflow
 *   If b < 0 and a < Integer.MIN_VALUE - b  --> Underflow
 *
 * Multiplication Overflow Conditions:
 *   If a > 0, b > 0 and a > Integer.MAX_VALUE / b  --> Overflow
 *   If a > 0, b < 0 and b < Integer.MIN_VALUE / a  --> Underflow
 *   If a < 0, b > 0 and a < Integer.MIN_VALUE / b  --> Underflow
 *   If a < 0, b < 0 and a < Integer.MAX_VALUE / b  --> Overflow
 *
 * Java 8+ provides `Math.addExact` and `Math.multiplyExact` which throw `ArithmeticException`.
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

bool willAdditionOverflow(int a, int b) {
        if (b > 0 && a > INT_MAX - b) return true;
        if (b < 0 && a < INT_MIN - b) return true;
        return false;
    }

    bool willMultiplicationOverflow(int a, int b) {
        if (a == 0 || b == 0) return false;
        if (a > 0) {
            if (b > 0) return a > INT_MAX / b;
            else       return b < INT_MIN / a;
        } else {
            if (b > 0) return a < INT_MIN / b;
            else       return a < INT_MAX / b;
        }
    }

    int main(void) {
        printf("=== 32-bit int Addition Overflow Tests ===\n");
        int** addPairs = {
            { 1000, 2000 },
            { INT_MAX, 1 },
            { INT_MAX - 10, 15 },
            { INT_MIN, -1 }
        };

        for (int* pair : addPairs) {
            int a = pair[0], b = pair[1];
            bool manualCheck = willAdditionOverflow(a, b);
            bool builtInThrew = false;
            try {
                Math.addExact(a, b);
            } catch (ArithmeticException e) {
                builtInThrew = true;
            }
            printf("Add(%d, %d) -> Manual Overflow: %-5b | Math.addExact Threw: %-5b\n",
                    a, b, manualCheck, builtInThrew);
        }

        printf("\n=== 32-bit int Multiplication Overflow Tests ===\n");
        int** multPairs = {
            { 100, 500 },
            { 100000, 100000 },
            { INT_MAX / 2, 3 },
            { -100000, 100000 }
        };

        for (int* pair : multPairs) {
            int a = pair[0], b = pair[1];
            bool manualCheck = willMultiplicationOverflow(a, b);
            bool builtInThrew = false;
            try {
                Math.multiplyExact(a, b);
            } catch (ArithmeticException e) {
                builtInThrew = true;
            }
            printf("Mult(%d, %d) -> Manual Overflow: %-5b | Math.multiplyExact Threw: %-5b\n",
                    a, b, manualCheck, builtInThrew);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant integer comparisons and divisions.
 * Space Complexity: O(1) - Zero extra heap memory.
 */
