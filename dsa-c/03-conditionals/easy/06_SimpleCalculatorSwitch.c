/**
 * Problem Statement:
 * Implement a simple command-line calculator that takes two operands `a` and `b`
 * and an operator character (+, -, *, /, %, ^ for power) and returns the evaluated result.
 * Safely guard against division and modulo by zero using conditionals.
 *
 * Asked in: TCS, Wipro, Capgemini, Accenture
 *
 * Approach:
 * - Use modern switch expression with yield/arrow syntax.
 * - Operator cases:
 *   '+' -> a + b
 *   '-' -> a - b
 *   '*' -> a * b
 *   '/' -> guard against b == 0, then a / b
 *   '%' -> guard against b == 0, then a % b
 *   '^' -> Math.pow(a, b)
 *   default -> throw IllegalArgumentException
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

double calculate(double a, double b, char op) {
        return switch (op) {
            case '+' -> a + b;
            case '-' -> a - b;
            case '*' -> a * b;
            case '/' -> {
                if (b == 0.0) {
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                }
                yield a / b;
            }
            case '%' -> {
                if (b == 0.0) {
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                }
                yield a % b;
            }
            case '^' -> pow(a, b);
            default  -> fprintf(stderr, "Exception: invalid argument
"); return 0;
        };
    }

    int main(void) {
        printf("=== Modern Java Switch-Based Arithmetic Calculator ===\n");

        Object[][] testCalculations = {
            { 10.0, 4.0, '+' },
            { 15.5, 3.5, '-' },
            { 6.0, 7.0, '*' },
            { 22.0, 7.0, '/' },
            { 17.0, 5.0, '%' },
            { 2.0, 8.0, '^' },
            { 10.0, 0.0, '/' } // Division by zero test
        };

        for (Object[] row : testCalculations) {
            double a = (double) row[0];
            double b = (double) row[1];
            char op = (char) row[2];

            try {
                double result = calculate(a, b, op);
                printf("%.1f %c %.1f = %.4f\n", a, op, b, result);
            } catch (Exception e) {
                printf("%.1f %c %.1f ==> Exception Caught: %s\n", a, op, b, e.getMessage());
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant branch evaluation.
 * Space Complexity: O(1) - Stack variables only.
 */
