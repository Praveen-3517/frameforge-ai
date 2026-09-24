/**
 * Problem Statement:
 * Given two integers `a` and `b`, return the difference `(a - b)` without using the
 * subtraction (-) or addition (+) operators.
 *
 * Asked in: Microsoft, Qualcomm, Oracle, Cisco
 *
 * Approach:
 * - Approach 1: Two's Complement Addition:
 *   In two's complement representation: `-b = ~b + 1`.
 *   Therefore: `a - b = add(a, add(~b, 1))` using our bitwise adder logic.
 * - Approach 2: Direct Full Subtractor Circuit:
 *   1. Difference without borrow: `a ^ b`
 *   2. Borrow bits: `(~a & b) << 1` (borrow is required when subtracting 1 from 0)
 *   3. Iterate until borrow is 0:
 *      `int borrow = (~a & b) << 1;`
 *      `a = a ^ b;`
 *      `b = borrow;`
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

// Approach 1: Direct Full-Subtractor circuit with borrow
    int subtract(int a, int b) {
        while (b != 0) {
            int borrow = (~a & b) << 1; // Borrow bit occurs when 0 - 1
            a = a ^ b;                 // Difference without borrow
            b = borrow;
        }
        return a;
    }

    // Approach 2: Using Two's complement negation (~b + 1) and Bitwise Adder
    int add(int x, int y) {
        while (y != 0) {
            int carry = (x & y) << 1;
            x = x ^ y;
            y = carry;
        }
        return x;
    }

    int subtractViaTwosComplement(int a, int b) {
        int negB = add(~b, 1);
        return add(a, negB);
    }

    int main(void) {
        printf("=== Subtract Two Integers Without '-' or '+' Operators ===\n");

        int** testCases = {
            { 15, 6 },
            { 6, 15 },
            { 0, 10 },
            { 10, 0 },
            { -10, -5 },
            { -5, -10 },
            { 100, -50 },
            { 2147483640, 40 }
        };

        for (int* tc : testCases) {
            int a = tc[0];
            int b = tc[1];
            int res1 = subtract(a, b);
            int res2 = subtractViaTwosComplement(a, b);
            printf("Subtract(%d, %d) ==> Subtractor: %d | TwosComp: %d | Expected: %d\n",
                    a, b, res1, res2, a - b);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Loop runs at most 32 iterations for 32-bit integers.
 * Space Complexity: O(1) - Constant auxiliary stack registers.
 */
