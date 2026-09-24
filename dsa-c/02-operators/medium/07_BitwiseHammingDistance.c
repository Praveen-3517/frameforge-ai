/**
 * Problem Statement:
 * The Hamming distance between two integers is the number of positions at which
 * the corresponding bits are different.
 * Given two integers `x` and `y`, return the Hamming distance between them.
 * (LeetCode 461: Hamming Distance).
 *
 * Example:
 * x = 1 (0 0 0 1)
 * y = 4 (0 1 0 0)
 * Differ at 2 bit positions -> Output: 2
 *
 * Asked in: Facebook / Meta, Amazon, Twitter, Bloomberg
 *
 * Approach:
 * - Bitwise XOR Property:
 *   The XOR of x and y (`x ^ y`) produces a binary number where each bit is 1
 *   if and only if the corresponding bits in x and y differ.
 * - Counting Set Bits:
 *   The problem reduces directly to counting the number of 1s in `(x ^ y)`.
 *   Using Brian Kernighan's algorithm `n = n & (n - 1)`, we count only the 1-bits
 *   in O(number of differing bits) time.
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

int hammingDistance(int x, int y) {
        int xor = x ^ y;
        int distance = 0;

        while (xor != 0) {
            xor &= (xor - 1); // Clears the lowest set bit
            distance++;
        }

        return distance;
    }

    int main(void) {
        printf("=== LeetCode 461: Hamming Distance (XOR + Kernighan) ===\n");

        int** testPairs = {
            { 1, 4 },
            { 3, 1 },
            { 0, 0 },
            { 0, 255 },
            { 0x55555555, 0xAAAAAAAA }, // Completely complementary 32-bit patterns
            { -1, 0 }
        };

        for (int* pair : testPairs) {
            int x = pair[0];
            int y = pair[1];
            int dist = hammingDistance(x, y);
            int builtin = int.bitCount(x ^ y);
            printf("x = %11d, y = %11d ==> Hamming Distance: %2d (Verified: %s)\n",
                    x, y, dist, dist == builtin ? "OK" : "FAIL");
        }
        return 0;
}

/*
 * Time Complexity: O(k) where k is the number of differing bits (at most 32).
 * Space Complexity: O(1) - Constant stack space.
 */
