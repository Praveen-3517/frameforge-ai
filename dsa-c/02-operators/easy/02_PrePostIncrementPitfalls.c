/**
 * Problem Statement:
 * Analyze and demonstrate Java's increment and decrement operators (++ and --):
 * 1. Difference between pre-increment (++x) and post-increment (x++).
 * 2. The classic Java trap: `x = x++` and why `x` remains unchanged.
 * 3. Left-to-right operand evaluation in compound expressions like `x++ + ++x`.
 *
 * Asked in: Amazon, TCS, Wipro, Cognizant, Capgemini
 *
 * Approach:
 * - Pre-increment (`++x`): Increments value first, then evaluates to new value.
 * - Post-increment (`x++`): Evaluates to current value first, then increments the variable.
 * - `x = x++` Trap:
 *   In Java, evaluation order is strictly Left-to-Right.
 *   The RHS `x++` produces the current value of x (say 5), and internally increments x to 6.
 *   Then the assignment `=` writes the produced value (5) back to x, wiping out the increment!
 * - In complex expressions: `int a = 5; int res = a++ + ++a * a--;`
 *   Break down step-by-step strictly from left to right.
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

void testAssignmentTrap() {
        printf("--- The Classic 'x = x++' Trap ---\n");
        int x = 5;
        x = x++;
        printf("Result of 'x = x++' when x was 5: " + x + " (Expected 5 in Java)\n");

        int y = 5;
        y = ++y;
        printf("Result of 'y = ++y' when y was 5: " + y + " (Expected 6)\n");
    }

    void testComplexExpression() {
        printf("\n--- Complex Multi-Operator Expression ---\n");
        int a = 5;
        // Evaluation order:
        // 1. a++ evaluates to 5, 'a' becomes 6
        // 2. ++a increments 'a' to 7, evaluates to 7
        // 3. a-- evaluates to 7, 'a' becomes 6
        // Precedence: * happens before +
        // res = 5 + (7 * 7) = 5 + 49 = 54
        int res = a++ + ++a * a--;
        printf("Expression: a++ + ++a * a-- (with initial a = 5)\n");
        printf("Computed Result: %d\n", res);
        printf("Final Value of a: %d\n", a);
    }

    void testLoopBehavior() {
        printf("\n--- Post-increment in Loop Condition ---\n");
        int count = 0;
        while (count++ < 3) {
            printf("Inside loop, count value is: %d\n", count);
        }
        printf("After loop, count value is: %d\n", count);
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Pre/Post Increment Mechanics & Gotchas ===\n");
        testAssignmentTrap();
        testComplexExpression();
        testLoopBehavior();
        return 0;
}

/*
 * Time Complexity: O(1) - Primitive register increments and loads.
 * Space Complexity: O(1) - Constant local variable storage.
 */
