/**
 * Problem Statement:
 * Given an integer `n`, return true if it is a power of two. Otherwise, return false.
 * An integer `n` is a power of two if there exists an integer `x` such that `n == 2^x`.
 * (LeetCode 231: Power of Two).
 *
 * Asked in: Google, Amazon, Microsoft, TCS
 *
 * Approach:
 * - A power of two in binary has exactly one bit set (e.g., 1=0001, 2=0010, 4=0100, 8=1000).
 * - Method 1: Brian Kernighan's Property:
 *   Subtracting 1 from `n` flips all bits up to and including the lowest set bit.
 *   Therefore, `n & (n - 1)` clears the single set bit. If `n` was a power of two, the result is 0!
 *   Condition: `n > 0 && (n & (n - 1)) == 0`
 * - Method 2: Lowest Set Bit Extraction:
 *   In two's complement, `-n = ~n + 1`.
 *   `n & (-n)` isolates the lowest set bit. If `(n & (-n)) == n`, it has only one set bit.
 *   Condition: `n > 0 && (n & (-n)) == n`
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

// Method 1: Turn off the rightmost set bit
    bool isPowerOfTwoBK(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

    // Method 2: Isolate the rightmost set bit
    bool isPowerOfTwoLSB(int n) {
        return n > 0 && (n & (-n)) == n;
    }

    int main(void) {
        printf("=== LeetCode 231: Power of Two (Bitwise O(1)) ===\n");

        int* testCases = {
            1, 2, 3, 4, 5, 8, 16, 1024, 0, -2, -16, INT_MIN, 1073741824
        };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            bool ans1 = isPowerOfTwoBK(n);
            bool ans2 = isPowerOfTwoLSB(n);
            printf("n = %11d ==> isPowerOfTwo: %-5s (LSB method: %s)\n", n, ans1, ans2);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Single bitwise AND comparison.
 * Space Complexity: O(1) - Uses only constant CPU registers.
 */
