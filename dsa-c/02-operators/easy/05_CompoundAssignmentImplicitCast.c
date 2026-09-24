/**
 * Problem Statement:
 * Explain and demonstrate why compound assignment operators (+=, -=, *=, etc.) behave differently
 * from standard assignment combined with binary operators in Java.
 * Specifically:
 * 1. Why does `short s = 5; s += 5;` compile cleanly, while `s = s + 5;` throws a compile error?
 * 2. Demonstrate silent overflow with `byte b = 127; b += 1;` wrapping to -128.
 * 3. Explore compound bitwise shift assignments (<<=, >>=, >>>=).
 *
 * Asked in: Oracle, Microsoft, Goldman Sachs, Amazon
 *
 * Approach:
 * - According to the Java Language Specification (JLS §15.26.2):
 *   A compound assignment expression of the form `E1 op= E2` is equivalent to:
 *   `E1 = (T)((E1) op (E2))`
 *   where `T` is the static type of `E1`, except that `E1` is evaluated only once.
 * - Therefore, the compiler automatically inserts an implicit narrowing cast!
 * - With `s = s + 5;`, `s + 5` promotes to `int`, which cannot be assigned to `short` without explicit `(short)`.
 * - With `s += 5;`, the compiler generates `s = (short)(s + 5);`, hiding narrowing truncations.
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

void demonstrateImplicitCast() {
        printf("--- 1. Why 's += 5' Compiles but 's = s + 5' Fails ---\n");
        short s = 5;

        // The line below would fail with: Type mismatch cannot convert from int to short
        // s = s + 5;

        // Compiles because it is desugared to: s = (short)(s + 5);
        s += 5;
        printf("%d%d%d\n", "short s after 's, = 5': ", s);

        // Explicit equivalent
        s = (short) (s + 5);
        printf("%d%d%d\n", "short s after explicit cast 's = (short)(s, 5)': ", s);
    }

    void demonstrateSilentOverflow() {
        printf("\n--- 2. Silent Overflow via Compound Assignment ---\n");
        signed char b = 127; // Maximum value of signed 8-bit signed char
        printf("Initial signed char b: %d\n", b);

        // Implicit cast causes wrap-around to -128 without any warning or error!
        b += 1;
        printf("signed char b after 'b += 1': " + b + " (Silent Two's Complement Overflow!)\n");

        b += 2;
        printf("%d%d%d\n", "signed char b after 'b, = 2': ", b);
    }

    void demonstrateCompoundBitwiseShifts() {
        printf("\n--- 3. Compound Bitwise Shift Operators ---\n");
        int num = 8;
        num <<= 2; // num = num * 4 = 32
        printf("8 <<= 2   : %d\n", num);

        num >>= 3; // num = num / 8 = 4
        printf("32 >>= 3  : %d\n", num);

        int neg = -16;
        neg >>>= 2; // Unsigned shift
        printf("-16 >>>= 2: " + neg + " (Sign bit cleared to 0)\n");
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Compound Assignment & Implicit Casting Trap ===\n");
        demonstrateImplicitCast();
        demonstrateSilentOverflow();
        demonstrateCompoundBitwiseShifts();
        return 0;
}

/*
 * Time Complexity: O(1) - Constant time CPU register operations.
 * Space Complexity: O(1) - Stack variables only.
 */
