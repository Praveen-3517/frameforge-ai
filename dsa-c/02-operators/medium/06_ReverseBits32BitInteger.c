/**
 * Problem Statement:
 * Reverse the bits of a given 32-bit unsigned integer.
 * (LeetCode 190: Reverse Bits).
 *
 * Example:
 * Input:  00000010100101000001111010011100 (43261596)
 * Output: 00111001011110000010100101000000 (964176192)
 *
 * Asked in: Apple, Google, Microsoft, Amazon, Nvidia
 *
 * Approach:
 * - Approach 1: Bit-by-bit shift (32 iterations)
 *   In each step, extract the LSB of `n` (`n & 1`), shift `result` left by 1 and OR the bit,
 *   then logical right shift `n >>>= 1`.
 * - Approach 2: Divide and Conquer / Parallel Bit Reversal (O(1) loopless):
 *   Just like merge sort, swap chunks of bits of decreasing size:
 *   1. Swap 16-bit halves: `(n >>> 16) | (n << 16)`
 *   2. Swap 8-bit bytes  : `((n & 0xFF00FF00) >>> 8) | ((n & 0x00FF00FF) << 8)`
 *   3. Swap 4-bit nibbles: `((n & 0xF0F0F0F0) >>> 4) | ((n & 0x0F0F0F0F) << 4)`
 *   4. Swap 2-bit pairs  : `((n & 0xCCCCCCCC) >>> 2) | ((n & 0x33333333) << 2)`
 *   5. Swap adjacent bits: `((n & 0xAAAAAAAA) >>> 1) | ((n & 0x55555555) << 1)`
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

// Approach 1: 32-step loop
    int reverseBitsLoop(int n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            result = (result << 1) | (n & 1);
            n >>>= 1;
        }
        return result;
    }

    // Approach 2: Divide & Conquer (5 constant-time mask swaps)
    int reverseBitsDivideConquer(int n) {
        n = (n >>> 16) | (n << 16);
        n = ((n & 0xFF00FF00) >>> 8) | ((n & 0x00FF00FF) << 8);
        n = ((n & 0xF0F0F0F0) >>> 4) | ((n & 0x0F0F0F0F) << 4);
        n = ((n & 0xCCCCCCCC) >>> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xAAAAAAAA) >>> 1) | ((n & 0x55555555) << 1);
        return n;
    }

    const char* toBinary32(int val) {
        return const char*.format("%32s", toBinaryString(val)).replace(' ', '0');
    }

    int main(void) {
        printf("=== LeetCode 190: Reverse Bits (32-Bit Unsigned int) ===\n");

        int* testCases = {
            43261596, // 00000010100101000001111010011100
            -3,       // 11111111111111111111111111111101
            1,        // 00000000000000000000000000000001
            0,
            -1
        };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            int rev1 = reverseBitsLoop(n);
            int rev2 = reverseBitsDivideConquer(n);
            printf("Input  : %11d | %s\n", n, toBinary32(n));
            printf("Loop   : %11d | %s\n", rev1, toBinary32(rev1));
            printf("D&C    : %11d | %s\n\n", rev2, toBinary32(rev2));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Exactly 32 operations (loop) or 5 operations (D&C).
 * Space Complexity: O(1) - Constant stack space.
 */
