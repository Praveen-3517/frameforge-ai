/**
 * Problem Statement:
 * Print numbers from 1 to N and from N to 1 recursively without using any loops (`for`, `while`, `do-while`).
 * Demonstrate the fundamental difference between:
 * 1. Head Recursion (actions execute after the recursive call during stack unwinding).
 * 2. Tail Recursion (actions execute before the recursive call during descent).
 *
 * Asked in: TCS, Wipro, Infosys, Cognizant
 *
 * Approach:
 * - Print 1 to N (Head Recursion / Stack Unwinding):
 *   `if (n == 0) return;`
 *   `print1ToN(n - 1);` // Recurse first
 *   `System.out.print(n + " ");` // Print on stack unwinding
 * - Print N to 1 (Tail Recursion / Pre-order descent):
 *   `if (n == 0) return;`
 *   `System.out.print(n + " ");` // Print before recursing
 *   `printNTo1(n - 1);`
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

// Head Recursion: prints 1 to N
    void print1ToN(int n) {
        if (n == 0) return;
        print1ToN(n - 1);
        printf("%s", n + " ");
    }

    // Tail Recursion: prints N to 1
    void printNTo1(int n) {
        if (n == 0) return;
        printf("%s", n + " ");
        printNTo1(n - 1);
    }

    int main(void) {
        printf("=== Recursive Head vs Tail Printing (No Loops) ===\n");

        int n = 10;
        printf("Printing 1 to %d (Head Recursion) : ", n);
        print1ToN(n);
        printf("\n");

        printf("Printing %d to 1 (Tail Recursion) : ", n);
        printNTo1(n);
        printf("\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Exactly N recursive calls.
 * Space Complexity: O(N) - N frames on the JVM call stack.
 */
