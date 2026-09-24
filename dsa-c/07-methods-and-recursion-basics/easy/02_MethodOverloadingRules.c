/**
 * Problem Statement:
 * Demonstrate Java's Method Overloading resolution order:
 * Prove the exact compilation precedence hierarchy:
 *   1. Exact Match
 *   2. Widening Primitive Conversion (e.g. int -> long -> double)
 *   3. Autoboxing Conversion (int -> Integer)
 *   4. Varargs (int... args)
 *
 * Asked in: Oracle, TCS, Infosys, IBM
 *
 * Approach:
 * - Create overloaded variants:
 *   `print(int x)`
 *   `print(long x)`
 *   `print(Integer x)`
 *   `print(int... x)`
 * - Test which variant is chosen when various combinations of overloads are present.
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

void process(int x) {
        printf("-> Matched: Exact int\n");
    }

    void process(long long x) {
        printf("-> Matched: Widening to long long\n");
    }

    void process(int x) {
        printf("-> Matched: Autoboxing to int\n");
    }

    void process(int... x) {
        printf("-> Matched: Varargs (int...)\n");
    }

    // Overload resolution between double and float
    void display(double d) {
        printf("-> Display: double %d\n", d);
    }

    void display(const char* s) {
        printf("-> Display: const char* %d\n", s);
    }

    int main(void) {
        printf("=== Java Method Overloading Precedence Hierarchy ===\n");

        int value = 42;
        printf("%s", "Invoking process(int 42)               ");
        process(value); // Hits exact int

        long long longVal = 100L;
        printf("%s", "Invoking process(long long 100L)            ");
        process(longVal); // Hits long long

        int obj = 200;
        printf("%s", "Invoking process(int 200)          ");
        process(obj); // Hits int

        printf("%s", "Invoking process(1, 2, 3)              ");
        process(1, 2, 3); // Hits varargs
        return 0;
}

/*
 * Time Complexity: O(1) - Overload resolution happens entirely at COMPILE TIME.
 * Space Complexity: O(1) - Constant stack frames.
 */
