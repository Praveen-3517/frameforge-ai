/**
 * Problem Statement:
 * Demonstrate the behavior of Java's arithmetic operators (+, -, *, /, %) with special attention to:
 * 1. Integer division truncation (towards zero).
 * 2. Division and modulo by zero exceptions (ArithmeticException for ints vs Infinity/NaN for floats).
 * 3. Modulo behavior with negative numbers: (-a % b), (a % -b), and comparison with Math.floorMod().
 *
 * Asked in: TCS, Infosys, Cognizant, Wipro
 *
 * Approach:
 * - In Java, integer division truncates decimal fractions towards 0: 7 / 2 = 3 and -7 / 2 = -3.
 * - Floating point division by zero yields Infinity or NaN, never throwing ArithmeticException.
 * - The sign of `a % b` in Java always takes the sign of dividend `a`.
 * - `Math.floorMod(a, b)` follows mathematical Euclidean definition where the result matches the sign of divisor `b`.
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

void demonstrateDivision() {
        printf("--- int Truncation vs Float Division ---\n");
        int a = 7, b = 2;
        printf("7 / 2 (int)         : %d\n", (a / b));
        printf("-7 / 2 (int)        : %d\n", (-a / b));
        printf("7.0 / 2 (double)    : %d\n", (7.0 / b));
        printf("1.0 / 0.0 (float)   : %d\n", (1.0 / 0.0));
        printf("-1.0 / 0.0 (float)  : %d\n", (-1.0 / 0.0));
        printf("0.0 / 0.0 (float)   : %d\n", (0.0 / 0.0));
    }

    void demonstrateModuloRules() {
        printf("\n--- Java % Operator vs Math.floorMod() ---\n");
        int** pairs = { { 7, 3 }, { -7, 3 }, { 7, -3 }, { -7, -3 } };

        for (int* p : pairs) {
            int dividend = p[0];
            int divisor = p[1];
            int javaMod = dividend % divisor;
            int mathFloorMod = Math.floorMod(dividend, divisor);

            printf("%4d %% %4d ==> Java %%: %2d | Math.floorMod(): %2d\n",
                    dividend, divisor, javaMod, mathFloorMod);
        }
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Arithmetic Operators & Modulo Deep Dive ===\n");
        demonstrateDivision();
        demonstrateModuloRules();
        return 0;
}

/*
 * Time Complexity: O(1) - Constant time CPU arithmetic operations.
 * Space Complexity: O(1) - Uses only stack registers.
 */
