/**
 * Problem Statement:
 * Swap two numerical variables without using any temporary third variable.
 * Demonstrate two standard approaches:
 * 1. Arithmetic Addition & Subtraction (caution: overflow risks)
 * 2. Bitwise XOR Operator (immune to arithmetic overflow)
 *
 * Asked in: TCS, Cognizant, Wipro, Infosys
 *
 * Approach:
 * Method 1 (Arithmetic):
 *   a = a + b
 *   b = a - b   // (a + b) - b = a
 *   a = a - b   // (a + b) - a = b
 *
 * Method 2 (Bitwise XOR):
 *   a = a ^ b
 *   b = a ^ b   // (a ^ b) ^ b = a
 *   a = a ^ b   // (a ^ b) ^ a = b
 *
 * XOR is preferred because it avoids integer overflow when numbers are large.
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

void swapUsingArithmetic(int a, int b) {
        printf("Before Arithmetic Swap: a = %d, b = %d\n", a, b);
        a = a + b;
        b = a - b;
        a = a - b;
        printf("After Arithmetic Swap:  a = %d, b = %d\n", a, b);
    }

    void swapUsingXor(int a, int b) {
        printf("Before XOR Swap:        a = %d, b = %d\n", a, b);
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        printf("After XOR Swap:         a = %d, b = %d\n", a, b);
    }

    int main(void) {
        printf("=== Test Case 1: Standard Positive Numbers ===\n");
        swapUsingArithmetic(15, 25);
        printf("\n");
        swapUsingXor(15, 25);

        printf("\n=== Test Case 2: Negative Numbers ===\n");
        swapUsingArithmetic(-10, 40);
        printf("\n");
        swapUsingXor(-10, 40);

        printf("\n=== Test Case 3: Large Integers (Testing Overflow Safety of XOR) ===\n");
        int x = INT_MAX - 5;
        int y = INT_MAX - 10;
        // Arithmetic swap might trigger silent two's complement wrap-around, but XOR operates strictly bitwise
        swapUsingXor(x, y);
        return 0;
}

/*
 * Time Complexity: O(1) - Constant time 3-operation assignment sequence.
 * Space Complexity: O(1) - In-place manipulation with zero extra memory allocated.
 */
