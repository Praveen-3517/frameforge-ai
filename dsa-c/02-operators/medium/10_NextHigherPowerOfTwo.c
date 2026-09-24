/**
 * Problem Statement:
 * Given an integer `n`, find the smallest power of two that is greater than or equal to `n`.
 * Replicate and explain the exact bit-smearing algorithm used internally by Oracle inside
 * Java's `java.util.HashMap#tableSizeFor(int cap)`.
 *
 * Example:
 * n = 5  -> 8
 * n = 16 -> 16
 * n = 17 -> 32
 *
 * Asked in: Oracle, Amazon, Google, High-Frequency Trading (HFT) Systems
 *
 * Approach:
 * - The Bit-Smearing Algorithm:
 *   1. Subtract 1 (`int x = n - 1`):
 *      If `n` is already a power of 2 (e.g. 16 = 10000_2), we want to return 16, not 32.
 *      Subtracting 1 gives 15 (01111_2), ensuring the subsequent smearing produces 15, which plus 1 yields 16.
 *   2. Smear the leading 1-bit across all lower bit positions using unsigned right shifts and OR:
 *      x |= x >>> 1;  // Sets 2 adjacent bits to 1
 *      x |= x >>> 2;  // Sets 4 adjacent bits to 1
 *      x |= x >>> 4;  // Sets 8 adjacent bits to 1
 *      x |= x >>> 8;  // Sets 16 adjacent bits to 1
 *      x |= x >>> 16; // Sets all 32 bits from MSB down to 1
 *   3. Result is of the form `00...01111111`.
 *   4. Adding 1 (`x + 1`) flips all 1s to 0 and carries 1 to the next power of 2 (`00...10000000`)!
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

// Java JDK HashMap.tableSizeFor implementation
    int nextPowerOfTwo(int n) {
        if (n <= 0) return 1;
        int x = n - 1;
        x |= x >>> 1;
        x |= x >>> 2;
        x |= x >>> 4;
        x |= x >>> 8;
        x |= x >>> 16;
        return x + 1;
    }

    int main(void) {
        printf("=== Java HashMap tableSizeFor: Next Power of Two via Bit Smearing ===\n");

        int* testCases = { 0, 1, 2, 3, 5, 8, 9, 15, 16, 17, 31, 32, 33, 100, 1023, 1024, 1025 };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            int nextPow = nextPowerOfTwo(n);
            printf("n = %4d ==> Next Power of 2: %4d | Binary: %s\n",
                    n, nextPow, toBinaryString(nextPow));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Exactly 5 bitwise shifts and OR operations (no loops).
 * Space Complexity: O(1) - Single 32-bit register.
 */
