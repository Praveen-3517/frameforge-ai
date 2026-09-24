/**
 * Problem Statement:
 * Demonstrate the internal behavior of the Java String Constant Pool (SCP),
 * String immutability, the difference between `==` and `.equals()`, and `String.intern()`.
 *
 * Asked in: Amazon, Oracle, TCS, Infosys, Cognizant
 *
 * Approach:
 * - String Literals:
 *   `String s1 = "java";` and `String s2 = "java";` point to the identical object in the SCP.
 *   `s1 == s2` evaluates to true!
 * - `new String("java")`:
 *   Forces allocation of a new `String` object on the heap outside the SCP.
 *   `s1 == s3` evaluates to false, but `s1.equals(s3)` evaluates to true.
 * - `s3.intern()`:
 *   Searches SCP for an equal string. If present, returns the SCP reference.
 *   `s1 == s3.intern()` evaluates to true!
 * - Compile-time constant folding:
 *   `"ja" + "va"` is folded at compile time into `"java"`.
 *   However, `String prefix = "ja"; prefix + "va"` is computed at runtime via `StringBuilder`
 *   and produces a new Heap object!
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

void testStringPool() {
        printf("--- 1. const char* Constant Pool & Reference Equality ---\n");

        const char* s1 = "hello";
        const char* s2 = "hello";
        const char* s3 = new const char*("hello");
        const char* s4 = s3.intern();

        printf("s1 == s2 (both literals)        : " + (s1 == s2) + " (Expected: true)\n");
        printf("s1 == s3 (literal vs new const char*): " + (s1 == s3) + " (Expected: false)\n");
        printf("(strcmp(s1, s3) == 0) (value check)     : " + (strcmp(s1, s3) == 0) + " (Expected: true)\n");
        printf("s1 == s3.intern() (SCP lookup)  : " + (s1 == s4) + " (Expected: true)\n");
    }

    void testConstantFolding() {
        printf("\n--- 2. Compile-Time Constant Folding vs Runtime Concatenation ---\n");

        const char* base = "hello";
        const char* folded = "hel" + "lo"; // Folded at compile time into "hello"
        const char* runtime = "hel";
        runtime = runtime + "lo";     // Evaluated at runtime via StringBuilder

        printf("base == folded (\"hel\" + \"lo\")    : " + (base == folded) + " (Expected: true)\n");
        printf("base == runtime (runtime + \"lo\")  : " + (base == runtime) + " (Expected: false)\n");
    }

    int main(void) {
        printf("=== Topic 06 (Easy): Java const char* Constant Pool (SCP) Mechanics ===\n");
        testStringPool();
        testConstantFolding();
        return 0;
}

/*
 * Time Complexity: O(1) for reference and intern pool checks.
 * Space Complexity: O(1) - Constant strings in bytecode constant pool.
 */
