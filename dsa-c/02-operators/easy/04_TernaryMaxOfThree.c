/**
 * Problem Statement:
 * Given three integers a, b, and c, determine the maximum and minimum values using
 * the ternary conditional operator (? :) without using Math.max / Math.min.
 * Also demonstrate the subtle Java numeric type promotion rules inside ternary expressions.
 *
 * Asked in: Capgemini, TCS, Wipro, Cognizant
 *
 * Approach:
 * - Nested Ternary:
 *   `max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);`
 * - Type Promotion Rule in Ternary:
 *   If the second and third operands of `? :` have different numeric types (e.g., int and double),
 *   the result is promoted to the common wider type (binary numeric promotion), even if the
 *   branch selected is an int!
 *   Example: `true ? 1 : 2.0` results in `1.0` (double)!
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

int findMax(int a, int b, int c) {
        return (a >= b) ? ((a >= c) ? a : c) : ((b >= c) ? b : c);
    }

    int findMin(int a, int b, int c) {
        return (a <= b) ? ((a <= c) ? a : c) : ((b <= c) ? b : c);
    }

    void testTypePromotionTrap() {
        printf("--- Ternary Type Promotion Trap ---\n");
        // Operand 2 is int (1), Operand 3 is double (2.0)
        // Expression evaluates to double 1.0, not int 1!
        Number result = true ? int.valueOf(1) : double.valueOf(2.0);
        printf("Expression: true ? int.valueOf(1) : double.valueOf(2.0)\n");
        printf("Result Value : %d\n", result);
        printf("Result Type  : %d\n", result.getClass().getName());

        char ch = true ? 'X' : 65536; // 65536 doesn't fit in char, promotes to int!
        printf("Expression: true ? 'X' : 65536 -> Promotes 'X' to ASCII int: %d\n", (int) ch);
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Ternary Conditional Operator & Type Promotion ===\n");

        int** testTriplets = {
            { 10, 25, 15 },
            { -5, -20, -1 },
            { 100, 100, 50 },
            { 42, 42, 42 }
        };

        for (int* t : testTriplets) {
            int a = t[0], b = t[1], c = t[2];
            int max = findMax(a, b, c);
            int min = findMin(a, b, c);
            printf("Inputs: (%d, %d, %d) ==> Max: %d | Min: %d\n", a, b, c, max, min);
        }

        printf("\n");
        testTypePromotionTrap();
        return 0;
}

/*
 * Time Complexity: O(1) - Constant number of comparisons.
 * Space Complexity: O(1) - Primitive register variables only.
 */
