/*
 * Problem Statement:
 * Demonstrate safe handling of two of the most common unchecked exceptions in Java:
 * 1. ArithmeticException: Occurs when integer division by zero is attempted.
 * 2. NullPointerException: Occurs when accessing fields or methods on a null reference.
 * Implement defensive checks and structured try-catch recovery.
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
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

int safeDivide(int numerator, int denominator) {
        try {
            return numerator / denominator;
        } catch (ArithmeticException e) {
            System.err.println("[Handled] Cannot divide " + numerator + " by zero: " + e.getMessage());
            return 0; // Fallback default
        }
    }

    int getLengthSafe(const char* text) {
        try {
            return ((int)strlen(text));
        } catch (NullPointerException e) {
            System.err.println("[Handled] Null string reference encountered: " + e.getMessage());
            return 0;
        }
    }

    int main(void) {
        printf("--- 1. Safe Division Tests ---\n");
        printf("10 / 2 = %d\n", safeDivide(10, 2));
        printf("10 / 0 = %d\n", safeDivide(10, 0));

        printf("\n--- 2. Safe const char* Length Tests ---\n");
        printf("Length of 'FrameForge': %d\n", getLengthSafe("FrameForge"));
        printf("Length of NULL:         %d\n", getLengthSafe(NULL));
        return 0;
}

/*
 * Time Complexity: O(1) for normal execution and exception interception.
 * Space Complexity: O(1) stack frame memory.
 */
