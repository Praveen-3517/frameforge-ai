/**
 * Problem Statement:
 * Compute the factorial of an integer `n` recursively:
 *   n! = n * (n - 1)! with base case 0! = 1 and 1! = 1.
 * Instrument the recursion to visually print the JVM Call Stack frames
 * (demonstrating stack pushes on entry and stack pops on return).
 * Discuss the cause and prevention of `java.lang.StackOverflowError`.
 *
 * Asked in: TCS, Infosys, Accenture, Cognizant
 *
 * Approach:
 * - Base Case: `if (n <= 1) return 1L;`
 * - Recursive Step: `return n * factorial(n - 1);`
 * - Indentation: Use depth-based space indentation to visualize the Call Stack tree.
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

long long factorialWithVisualization(int n, int depth) {
        const char* indent = "  ".repeat(depth);
        printf("%s-> [PUSH] Entering factorial(%d) | Stack Depth: %d\n", indent, n, depth);

        if (n <= 1) {
            printf("%s<- [BASE CASE REACHED] Returning 1 for factorial(%d)\n", indent, n);
            return 1L;
        }

        long long result = n * factorialWithVisualization(n - 1, depth + 1);

        printf("%s<- [POP]  Exiting factorial(%d) = %d\n", indent, n, result);
        return result;
    }

    int main(void) {
        printf("=== Recursive Factorial with JVM Call Stack Visualization ===\n");

        int n = 5;
        long long fact = factorialWithVisualization(n, 0);
        printf("\nFinal Calculated Factorial(%d): %d\n", n, fact);
        return 0;
}

/*
 * Time Complexity: O(N) - Exactly N recursive invocations.
 * Space Complexity: O(N) - N stack frames on the Call Stack.
 */
