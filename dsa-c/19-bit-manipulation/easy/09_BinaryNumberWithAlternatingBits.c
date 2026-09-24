/**
 * Problem: Binary Number with Alternating Bits (LeetCode 693)
 * Asked in: Microsoft, Amazon
 * 
 * Given a positive integer, check whether it has alternating bits:
 * namely, if two adjacent bits will always have different values.
 * 
 * Approach:
 * Bit Manipulation Trick:
 * If n has alternating bits, then n ^ (n >> 1) should produce all 1-bits
 * (a number of the form 000...111...).
 * A number m has all 1-bits iff m & (m + 1) == 0.
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

bool hasAlternatingBits(int n) {
        int m = n ^ (n >> 1);
        // m should be all 1s: 0001, 0011, 0111, etc.
        return (m & (m + 1)) == 0;
    }

    int main(void) {
        // 5 = 101 -> alternating
        printf("5 (101) alternating: " + hasAlternatingBits(5) + " (Expected: true)\n");
        // 7 = 111 -> not alternating
        printf("7 (111) alternating: " + hasAlternatingBits(7) + " (Expected: false)\n");
        // 11 = 1011 -> not alternating
        printf("11 (1011) alternating: " + hasAlternatingBits(11) + " (Expected: false)\n");
        // 10 = 1010 -> alternating
        printf("10 (1010) alternating: " + hasAlternatingBits(10) + " (Expected: true)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
