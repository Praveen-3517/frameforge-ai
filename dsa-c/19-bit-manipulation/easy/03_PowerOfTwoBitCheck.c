/**
 * Problem: Power of Two (LeetCode 231)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an integer n, return true if it is a power of two. Otherwise, return false.
 * An integer n is a power of two if there exists an integer x such that n == 2^x.
 * 
 * Approach:
 * Bit Manipulation:
 * A power of two has exactly one set bit in its binary representation.
 * n & (n - 1) clears the lowest set bit.
 * So if n > 0 and n & (n - 1) == 0, then n is a power of two!
 * 
 * Time Complexity: O(1)
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

bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

    int main(void) {
        printf("1 is power of 2: " + isPowerOfTwo(1) + " (Expected: true)\n");
        printf("16 is power of 2: " + isPowerOfTwo(16) + " (Expected: true)\n");
        printf("3 is power of 2: " + isPowerOfTwo(3) + " (Expected: false)\n");
        printf("0 is power of 2: " + isPowerOfTwo(0) + " (Expected: false)\n");
        printf("-16 is power of 2: " + isPowerOfTwo(-16) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
