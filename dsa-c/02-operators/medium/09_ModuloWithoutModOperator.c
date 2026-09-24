/**
 * Problem Statement:
 * Compute the modulo `n % d` without using the modulo (%) operator.
 * Address two scenarios:
 * 1. Fast Modulo when `d` is a known power of 2 (e.g., d = 2, 4, 8, 16, 64, 1024...).
 *    Explain why Java's `HashMap` forces capacity to be a power of two: `index = hash & (n - 1)`.
 * 2. General Modulo for arbitrary integer `d` using bitwise exponential shift subtraction.
 *
 * Asked in: Amazon, Oracle, Intel, Qualcomm, High Frequency Trading
 *
 * Approach:
 * - Scenario 1: Power of 2 (O(1)):
 *   When `d = 2^k`, the lowest k bits represent the remainder.
 *   `d - 1` creates a bitmask with the lowest k bits set to 1.
 *   `remainder = n & (d - 1);`
 *   This is 10x-20x faster than CPU hardware division instruction!
 * - Scenario 2: Arbitrary Divisor (O(log n)):
 *   Use exponential bit-shifting to subtract the largest multiple of `d` from `n`:
 *   Find highest `k` such that `(d << k) <= n`.
 *   Subtract `(d << k)` from `n` and repeat until `n < d`.
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

// Scenario 1: Fast Modulo for Power-of-Two Divisors
    int modPowerOfTwo(int n, int d) {
        // Precondition: d must be a positive power of 2
        return n & (d - 1);
    }

    // Scenario 2: General Modulo for any positive dividend and divisor
    int modGeneral(int n, int d) {
        if (d == 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        bool isNegativeDividend = n < 0;
        long long dividend = abs((long long) n);
        long long divisor = abs((long long) d);

        while (dividend >= divisor) {
            long long tempDivisor = divisor;
            while (dividend >= (tempDivisor << 1)) {
                tempDivisor <<= 1;
            }
            dividend -= tempDivisor;
        }

        int remainder = (int) dividend;
        return isNegativeDividend ? -remainder : remainder;
    }

    int main(void) {
        printf("=== Modulo Without '%' Operator (Power-of-2 vs General) ===\n");

        printf("--- 1. Power-of-Two Fast Modulo (HashMap Index Pattern) ---\n");
        int* powerDivisors = { 2, 4, 8, 16, 32, 64, 1024 };
        int sampleNum = 157;
        for (size_t _idx = 0; _idx < sizeof(powerDivisors)/sizeof(powerDivisors[0]); _idx++) {
        int d = powerDivisors[_idx];
            int fastMod = modPowerOfTwo(sampleNum, d);
            printf("%d & (%d - 1) = %3d (Java %%: %3d)\n", sampleNum, d, fastMod, sampleNum % d);
        }

        printf("\n--- 2. General Modulo for Arbitrary Divisors ---\n");
        int** testPairs = {
            { 157, 13 },
            { 100, 7 },
            { 25, 5 },
            { 3, 10 },
            { -45, 6 },
            { 1000000, 33 }
        };

        for (int* pair : testPairs) {
            int n = pair[0];
            int d = pair[1];
            int modVal = modGeneral(n, d);
            printf("%5d %% %2d ==> Bitwise Mod: %2d | Standard Java %%: %2d\n",
                    n, d, modVal, n % d);
        }
        return 0;
}

/*
 * Time Complexity:
 *   - Power-of-two: O(1) single cycle CPU instruction.
 *   - General: O(log^2 N) using exponential bit shifts.
 * Space Complexity: O(1) - Primitive register variables only.
 */
