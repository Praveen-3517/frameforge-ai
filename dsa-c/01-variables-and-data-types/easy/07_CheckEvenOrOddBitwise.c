/**
 * Problem Statement:
 * Determine whether a given integer is Even or Odd without using the modulo `%` operator.
 *
 * Asked in: Amazon, TCS, Microsoft
 *
 * Approach:
 * - Any integer's binary representation has its least significant bit (LSB) set to:
 *     `0` if Even (multiples of 2)
 *     `1` if Odd (2k + 1)
 * - Evaluating `(n & 1)`:
 *     If `(n & 1) == 0` -> Number is Even.
 *     If `(n & 1) == 1` -> Number is Odd.
 * - This bitwise check also naturally works for negative integers without extra logic.
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

bool isEven(int n) {
        return (n & 1) == 0;
    }

    bool isOdd(int n) {
        return (n & 1) != 0;
    }

    int main(void) {
        int* testNumbers = { 0, 4, 7, -8, -13, 1024, 1025 };

        printf("=== Bitwise Even/Odd Check (n & 1) ===\n");
        for (size_t _idx = 0; _idx < sizeof(testNumbers)/sizeof(testNumbers[0]); _idx++) {
        int n = testNumbers[_idx];
            const char* binary = toBinaryString(n);
            // Pad binary for clarity
            printf("Number: %-6d | LSB: %d | Status: %s\n",
                    n, (n & 1), isEven(n) ? "EVEN" : "ODD");
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Single CPU bitwise AND instruction.
 * Space Complexity: O(1) - Zero allocation.
 */
