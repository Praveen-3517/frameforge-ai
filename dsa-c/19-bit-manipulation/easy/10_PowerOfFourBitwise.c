/**
 * Problem: Power of Four (LeetCode 342)
 * Asked in: Google, Amazon
 * 
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 * An integer n is a power of four if there exists an integer x such that n == 4^x.
 * 
 * Approach - Pure Bit Manipulation (No Loops, No Log):
 * A power of four must:
 * 1. Be positive: n > 0
 * 2. Have exactly one set bit (power of 2): (n & (n - 1)) == 0
 * 3. That single set bit must be at an EVEN bit position (bit 0, 2, 4, 6, ...):
 *    4^0=1(bit0), 4^1=4(bit2), 4^2=16(bit4), 4^3=64(bit6)...
 *    Mask for even positions in 32-bit: 0x55555555 = 01010101...01010101
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

bool isPowerOfFour(int n) {
        return n > 0 
            && (n & (n - 1)) == 0           // exactly one set bit
            && (n & 0x55555555) != 0;       // set bit is at an even position
    }

    int main(void) {
        printf("1 is power of 4: " + isPowerOfFour(1) + " (Expected: true)\n");   // 4^0
        printf("4 is power of 4: " + isPowerOfFour(4) + " (Expected: true)\n");   // 4^1
        printf("16 is power of 4: " + isPowerOfFour(16) + " (Expected: true)\n"); // 4^2
        printf("5 is power of 4: " + isPowerOfFour(5) + " (Expected: false)\n");
        printf("2 is power of 4: " + isPowerOfFour(2) + " (Expected: false)\n");  // power of 2, not 4
        printf("8 is power of 4: " + isPowerOfFour(8) + " (Expected: false)\n");  // 2^3, not power of 4
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
