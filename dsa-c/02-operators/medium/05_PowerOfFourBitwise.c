/**
 * Problem Statement:
 * Given an integer `n`, return true if it is a power of four. Otherwise, return false.
 * Solve it in O(1) time without loops or recursion.
 * (LeetCode 342: Power of Four).
 *
 * Asked in: Google, Amazon, Microsoft, Adobe
 *
 * Approach:
 * - A number n is a power of 4 if and only if:
 *   1. It is strictly positive: `n > 0`
 *   2. It is a power of 2 (has exactly one bit set): `(n & (n - 1)) == 0`
 *   3. Its single set bit is at an EVEN bit position (0, 2, 4, 6, ..., 30).
 *      4^0 = 1    (bit 0)  -> 00000001
 *      4^1 = 4    (bit 2)  -> 00000100
 *      4^2 = 16   (bit 4)  -> 00010000
 *      4^3 = 64   (bit 6)  -> 01000000
 *   4. Even-bit mask: `0x55555555` (01010101010101010101010101010101)
 *      `n & 0x55555555` will be non-zero (in fact, equal to n).
 * - Alternative: Modulo 3 Property:
 *   4^x mod 3 = (3 + 1)^x mod 3 = 1^x mod 3 = 1.
 *   Every power of 4 has `n % 3 == 1`.
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

// Method 1: Bitmask 0x55555555 (Pure bitwise)
    bool isPowerOfFourBitmask(int n) {
        return (n > 0) && ((n & (n - 1)) == 0) && ((n & 0x55555555) == n);
    }

    // Method 2: Power of two + modulo 3
    bool isPowerOfFourMod3(int n) {
        return (n > 0) && ((n & (n - 1)) == 0) && (n % 3 == 1);
    }

    int main(void) {
        printf("=== LeetCode 342: Power of Four (O(1) Bitwise Solution) ===\n");

        int* testCases = {
            1, 4, 16, 64, 256, 1024,   // True
            2, 8, 32, 128, 512,        // False (powers of 2, but not 4)
            0, -4, -16, 5, 15,         // False
            1073741824                 // True: 4^15
        };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            bool ans1 = isPowerOfFourBitmask(n);
            bool ans2 = isPowerOfFourMod3(n);
            printf("n = %11d ==> Bitmask: %-5s | Mod3: %-5s\n", n, ans1, ans2);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant CPU bitwise instructions.
 * Space Complexity: O(1) - Stack variables only.
 */
