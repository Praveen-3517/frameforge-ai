/**
 * Problem Statement:
 * In Java, all numeric primitive types (byte, short, int, long) are signed (two's complement).
 * There are no native `unsigned int` keywords like in C/C++.
 * Demonstrate how to:
 * 1. Treat a 32-bit `int` as an unsigned 32-bit value [0, 2^32 - 1].
 * 2. Compare two integers as unsigned values.
 * 3. Divide and parse unsigned integers.
 * Compare manual masking `(n & 0xFFFFFFFFL)` with Java 8's `Integer.compareUnsigned`.
 *
 * Asked in: Google, Microsoft, Qualcomm
 *
 * Approach:
 * - Negative signed numbers (e.g., `-1`) have their MSB set to 1.
 * - In unsigned 32-bit arithmetic, `0xFFFFFFFF` is `4,294,967,295`, the maximum possible value!
 * - Standard signed comparison: `-1 < 1` is `true`.
 * - Unsigned comparison: `-1` (4294967295) `>` `1` is `true`!
 * - In Java 8+, `Integer.compareUnsigned(x, y)` provides this directly.
 * - Manually, we can convert both to `long` with `x & 0xFFFFFFFFL` and compare.
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

// Manual unsigned comparison using 64-bit mask
    int compareUnsignedManual(int x, int y) {
        long long ux = x & 0xFFFFFFFFL;
        long long uy = y & 0xFFFFFFFFL;
        return long long long long.compare(ux, uy);
    }

    const char* toUnsignedStringManual(int x) {
        long long ux = x & 0xFFFFFFFFL;
        return long long long long.toString(ux);
    }

    int main(void) {
        int a = -1; // Binary: 11111111 11111111 11111111 11111111
        int b = 1;  // Binary: 00000000 00000000 00000000 00000001

        printf("=== Signed vs. Unsigned int Semantics ===\n");
        printf("Variable a = " + a + " (Signed Decimal)\n");
        printf("Variable a = " + int.toUnsignedString(a) + " (Unsigned Decimal)\n");
        printf("Variable b = %d\n", b);

        printf("\n--- Comparison Results ---\n");
        printf("Standard Signed (a < b):       %d\n", (a < b)); // true (-1 < 1)
        printf("int.compareUnsigned(a, b): %d\n", (int.compareUnsigned(a, b) > 0 ? "a > b" : "a <= b")); // a > b
        printf("Manual Masked Compare(a, b):   %d\n", (compareUnsignedManual(a, b) > 0 ? "a > b" : "a <= b"));

        // Division demonstration
        int dividend = -1; // 4294967295
        int divisor = 2;
        int unsignedDivResult = int.divideUnsigned(dividend, divisor);
        printf("\nUnsigned Division of -1 (4294967295) / 2 = %d\n", int.toUnsignedString(unsignedDivResult));
        return 0;
}

/*
 * Time Complexity: O(1) - Single instruction primitive bitmasking and branchless comparison.
 * Space Complexity: O(1) - Stack allocation.
 */
