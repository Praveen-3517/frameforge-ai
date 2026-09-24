/**
 * Problem Statement:
 * Given a non-negative integer `n`, count the number of set bits (1s) in its binary representation.
 * Compare the naive bit-shifting approach with Brian Kernighan’s optimal Algorithm.
 * (LeetCode 191: Number of 1 Bits).
 *
 * Asked in: Google, Microsoft, Adobe, Cisco
 *
 * Approach:
 * Naive Approach:
 *   Loop through all 32 bits, checking `(n & 1)` and right-shifting. Runs in O(32) = O(1) always.
 *
 * Brian Kernighan’s Algorithm:
 *   In each step, perform `n = n & (n - 1)`.
 *   Subtracting 1 from a number flips all bits after the rightmost set bit, including the rightmost set bit itself.
 *   Therefore, `n & (n - 1)` clears the lowest set bit in `n`.
 *   Loop runs strictly proportional to the number of SET bits (Hamming weight), not total bits.
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

// Method 1: Naive 32-bit Shift
    int countBitsNaive(int n) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            count += (n & 1);
            n >>>= 1; // Unsigned right shift
        }
        return count;
    }

    // Method 2: Brian Kernighan's Algorithm (Optimal)
    int countBitsKernighan(int n) {
        int count = 0;
        while (n != 0) {
            n = n & (n - 1); // Clears the lowest set bit
            count++;
        }
        return count;
    }

    int main(void) {
        int* testCases = { 0, 1, 7, 15, 1024, 1023, -1, INT_MAX };

        printf("=== Hamming Weight (Set Bits Count) ===\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            int naive = countBitsNaive(n);
            int kernighan = countBitsKernighan(n);
            int builtIn = int.bitCount(n);

            printf("Number: %-12d | Binary: %-32s | Kernighan: %2d | BuiltIn: %2d\n",
                    n, toBinaryString(n), kernighan, builtIn);

            assert kernighan == builtIn : "Mismatch with built-in!";
        }
        printf("All test cases matched successfully!\n");
        return 0;
}

/*
 * Time Complexity:
 *   - Naive: O(32) = O(1) fixed.
 *   - Brian Kernighan: O(K) where K is the count of set bits (1 <= K <= 32).
 * Space Complexity: O(1) - Pure register manipulation.
 */
