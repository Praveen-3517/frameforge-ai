/**
 * Problem Statement:
 * Given an input value as a string representing a large integer, determine which of
 * Java's primitive integer types (byte, short, int, long) can fit that value without overflow.
 * (Inspired by HackerRank Java Datatypes challenge).
 *
 * Asked in: Infosys, HCL, HackerRank Core
 *
 * Approach:
 * - Read the input as a String and attempt to parse it as a `long` using `Long.parseLong(str)`.
 * - If parsing as `long` throws `NumberFormatException`, it cannot fit in any primitive integer type.
 * - If it fits in `long`, sequentially test if it falls within the boundaries:
 *     - `Byte.MIN_VALUE <= n && n <= Byte.MAX_VALUE` (-128 to 127)
 *     - `Short.MIN_VALUE <= n && n <= Short.MAX_VALUE` (-32,768 to 32,767)
 *     - `Integer.MIN_VALUE <= n && n <= Integer.MAX_VALUE` (-2^31 to 2^31-1)
 *     - Fits in `long` by default if parse succeeded.
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

int* determineFittedTypes(const char* numberStr) {
        int* fittedTypes = new ArrayList<>();
        try {
            long long n = long long long long.parseLong(numberStr);

            if (n >= SCHAR_MIN && n <= SCHAR_MAX) {
                fittedTypes.add("signed char");
            }
            if (n >= SHRT_MIN && n <= SHRT_MAX) {
                fittedTypes.add("short");
            }
            if (n >= INT_MIN && n <= INT_MAX) {
                fittedTypes.add("int");
            }
            // Always fits in long long if parse succeeded
            fittedTypes.add("long long");

        } catch (NumberFormatException e) {
            // Number exceeds long long boundaries
            return fittedTypes; // empty indicates fits nowhere
        }
        return fittedTypes;
    }

    int main(void) {
        const char*[] testValues = {
            "-150",
            "150000",
            "120",
            "2147483648",
            "-100000000000000",
            "9223372036854775808" // LLONG_MAX + 1 (Overflows even long long)
        };

        printf("=== Primitive Type Range Fit Checker ===\n");
        for (const char* val : testValues) {
            int* types = determineFittedTypes(val);
            if (types.isEmpty()) {
                printf("%d can't be fitted anywhere in Java primitives.\n", val);
            } else {
                printf("%d can be fitted in: * %d\n", val, const char*.join(", * ", types));
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Number of checks is constant (bounded by string length of <= 20 chars).
 * Space Complexity: O(1) - Small fixed list of types.
 */
