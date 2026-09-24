/**
 * Problem: Sum of Two Integers Without + or - (LeetCode 371)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given two integers a and b, return the sum of the two integers
 * without using the operators + and -.
 * 
 * Approach - Full Adder via Bit Manipulation:
 * A full adder:
 * - sum bits (no carry) = a ^ b
 * - carry bits = (a & b) << 1
 * Repeat until carry becomes 0.
 * 
 * Time Complexity: O(1) - max 32 iterations.
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

int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a = a ^ b;   // sum without carry
            b = carry;   // carry propagated
        }
        return a;
    }

    int main(void) {
        printf("1 + 2 = " + getSum(1, 2) + " (Expected: 3)\n");
        printf("2 + 3 = " + getSum(2, 3) + " (Expected: 5)\n");
        printf("-1 + 1 = " + getSum(-1, 1) + " (Expected: 0)\n");
        printf("-7 + 3 = " + getSum(-7, 3) + " (Expected: -4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
