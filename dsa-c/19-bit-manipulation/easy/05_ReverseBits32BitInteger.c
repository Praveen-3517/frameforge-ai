/**
 * Problem: Reverse Bits (LeetCode 190)
 * Asked in: Apple, Amazon, Microsoft
 * 
 * Reverse bits of a given 32 bits unsigned integer.
 * 
 * Approach:
 * Bit-by-bit extraction and placement:
 * For each of the 32 bit positions:
 * 1. Extract the LSB of n: bit = n & 1
 * 2. Left-shift result by 1 and OR in the extracted bit.
 * 3. Right-shift n by 1 (logical shift >>> to avoid sign extension).
 * 
 * Time Complexity: O(32) = O(1)
 * Space Complexity: O(1)
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

int reverseBits(int n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            result = (result << 1) | (n & 1);
            n >>>= 1;
        }
        return result;
    }

    int main(void) {
        // 43261596 = 00000010100101000001111010011100
        // Reversed = 00111001011110000010100101000000 = 964176192
        printf("Reversed 43261596: " + reverseBits(43261596) + " (Expected: 964176192)\n");

        // -3 in 32-bit = 11111111111111111111111111111101
        // Reversed    = 10111111111111111111111111111111 = -1073741825
        printf("Reversed -3: " + reverseBits(-3) + " (Expected: -1073741825)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
