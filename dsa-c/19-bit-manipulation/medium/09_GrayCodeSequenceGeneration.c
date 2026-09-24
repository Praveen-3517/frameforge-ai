/**
 * Problem: Gray Code (LeetCode 89)
 * Asked in: Amazon, Google, Microsoft
 * 
 * An n-bit gray code sequence is a sequence of 2^n integers where:
 * - Every integer is in the inclusive range [0, 2^n - 1].
 * - The first integer is 0.
 * - An integer appears no more than once.
 * - The binary representation of every pair of adjacent integers differ by exactly one bit.
 * - The binary representation of the first and last integers differ by exactly one bit.
 * Return any valid n-bit gray code sequence.
 * 
 * Approach - Binary-to-Gray Formula:
 * Gray code for integer i: i ^ (i >> 1)
 * Simply iterate i from 0 to 2^n - 1 and apply the formula.
 * 
 * Time Complexity: O(2^N)
 * Space Complexity: O(2^N)
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

int* grayCode(int n) {
        int total = 1 << n; // 2^n
        int* result = new ArrayList<>(total);
        for (int i = 0; i < total; i++) {
            result.add(i ^ (i >> 1));
        }
        return result;
    }

    int main(void) {
        printf("Gray code (n=2): %d\n", grayCode(2));
        // Expected: [0, 1, 3, 2] or any valid sequence

        printf("Gray code (n=3): %d\n", grayCode(3));
        // Expected: [0, 1, 3, 2, 6, 7, 5, 4] or any valid sequence
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
