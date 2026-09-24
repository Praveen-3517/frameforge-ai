/**
 * Problem Statement:
 * Given two signed integers `x` and `y`, determine if they have opposite signs
 * without using conditional branching (if-else statements) or library functions.
 *
 * Example:
 * (10, -20) -> true
 * (-5, -8)  -> false
 * (0, -1)   -> true
 *
 * Asked in: Bloomberg, Goldman Sachs, Adobe, Intel
 *
 * Approach:
 * - Two's Complement MSB Analysis:
 *   In signed 32-bit integers, the sign is stored exclusively in the most significant bit (MSB, bit 31):
 *   - MSB = 0 for positive numbers and zero.
 *   - MSB = 1 for negative numbers.
 * - Bitwise XOR Property:
 *   The XOR operator (^) returns 1 if and only if the corresponding bits are different.
 *   Therefore, if `x` and `y` have opposite signs, their MSBs differ, making the MSB of `(x ^ y)` equal to 1.
 *   A number with MSB = 1 in two's complement is strictly negative:
 *   `boolean oppositeSigns = (x ^ y) < 0;`
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

// Branchless sign check via XOR
    bool hasOppositeSigns(int x, int y) {
        return (x ^ y) < 0;
    }

    int main(void) {
        printf("=== Branchless Sign Check Using Bitwise XOR ===\n");

        int** testPairs = {
            { 10, -20 },
            { -5, -8 },
            { 100, 200 },
            { -1, 1 },
            { 0, -5 },
            { 0, 5 },
            { INT_MIN, INT_MAX }
        };

        for (int* pair : testPairs) {
            int x = pair[0];
            int y = pair[1];
            bool result = hasOppositeSigns(x, y);
            printf("Pair (%11d, %11d) ==> Opposite Signs: %s\n", x, y, result);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Single bitwise XOR and comparison instruction.
 * Space Complexity: O(1) - No memory allocations.
 */
