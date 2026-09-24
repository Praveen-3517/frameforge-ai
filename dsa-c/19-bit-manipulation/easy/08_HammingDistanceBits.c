/**
 * Problem: Hamming Distance (LeetCode 461)
 * Asked in: Amazon, Google, Microsoft
 * 
 * The Hamming distance between two integers is the number of positions at which
 * the corresponding bits are different.
 * Given two integers x and y, return the Hamming distance between them.
 * 
 * Approach:
 * 1. XOR x and y: the result has 1-bits exactly where x and y differ.
 * 2. Count the set bits in x ^ y using Kernighan's algorithm.
 * 
 * Time Complexity: O(1) - at most 32 iterations.
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

int hammingDistance(int x, int y) {
        int xorResult = x ^ y;
        int count = 0;
        while (xorResult != 0) {
            xorResult &= (xorResult - 1); // clear lowest set bit
            count++;
        }
        return count;
    }

    int main(void) {
        // 1 = 0001, 4 = 0100 -> differ at bits 0 and 2
        printf("Hamming(1, 4): " + hammingDistance(1, 4) + " (Expected: 2)\n");

        // 3 = 011, 1 = 001 -> differ at bit 1
        printf("Hamming(3, 1): " + hammingDistance(3, 1) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
