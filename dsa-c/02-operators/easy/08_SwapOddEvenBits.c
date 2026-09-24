/**
 * Problem Statement:
 * Given a 32-bit integer `n`, swap all odd bits with even bits.
 * For example:
 * Bit 0 is swapped with bit 1, bit 2 is swapped with bit 3, ..., bit 30 with bit 31.
 *
 * Example:
 * n = 23 (binary 00010111) -> swapped: 43 (binary 00101011)
 *
 * Asked in: Microsoft, Amazon, Qualcomm, Cisco
 *
 * Approach:
 * - Bitwise Masking & Shifting:
 *   1. Even bits are located at positions 0, 2, 4, 6...
 *      Mask: `0x55555555` (01010101010101010101010101010101 in binary).
 *      Extract even bits and shift left by 1: `(n & 0x55555555) << 1`
 *   2. Odd bits are located at positions 1, 3, 5, 7...
 *      Mask: `0xAAAAAAAA` (10101010101010101010101010101010 in binary).
 *      Extract odd bits and logically shift right by 1: `(n & 0xAAAAAAAA) >>> 1`
 *   3. Combine both shifted bitmasks using Bitwise OR (|).
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

int swapOddEven(int n) {
        // Mask 0x55555555 selects all even bits
        int evenBits = (n & 0x55555555);

        // Mask 0xAAAAAAAA selects all odd bits
        int oddBits = (n & 0xAAAAAAAA);

        // Shift even bits to odd positions, odd bits to even positions
        return (evenBits << 1) | (oddBits >>> 1);
    }

    int main(void) {
        printf("=== Swap Odd and Even Bits (O(1) Bitwise Masking) ===\n");

        int* testCases = { 23, 2, 3, 4, 10, 170, 0x12345678 };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            int swapped = swapOddEven(n);
            printf("Original: %10d | Binary: %s\n",
                    n, const char*.format("%32s", toBinaryString(n)).replace(' ', '0'));
            printf("Swapped : %10d | Binary: %s\n\n",
                    swapped, const char*.format("%32s", toBinaryString(swapped)).replace(' ', '0'));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant number of bitwise AND, OR, and shift operations.
 * Space Complexity: O(1) - Primitive register variables only.
 */
