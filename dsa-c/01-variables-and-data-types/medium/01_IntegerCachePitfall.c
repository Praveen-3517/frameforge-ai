/**
 * Problem Statement:
 * Demonstrate Java's Integer Cache mechanism (-128 to 127).
 * Explain why comparing two `Integer` wrapper objects with `==` returns `true`
 * for values within [-128, 127] but returns `false` outside that range.
 *
 * Asked in: Amazon, Oracle, Goldman Sachs, Morgan Stanley
 *
 * Approach:
 * - Java specification mandates caching of `Integer` objects between -128 and 127 via `Integer.valueOf(int)`.
 * - Autoboxing (e.g., `Integer a = 100;`) calls `Integer.valueOf(100)`, returning the shared instance from the cache.
 * - For values >= 128 or <= -129, `Integer.valueOf()` instantiates a distinct new `Integer` object on the heap.
 * - Comparing with `==` checks reference equality (memory addresses), which produces unexpected `false` for values >= 128.
 * - Always use `.equals()` to check numeric equivalence.
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

void testCacheComparison(int val) {
        int objA = val; // Autoboxing -> int.valueOf(val)
        int objB = val;

        bool refEqual = (objA == objB);
        bool valEqual = (strcmp(objA, objB) == 0);

        printf("Value: %-5d | objA == objB (Reference): %-6b | (strcmp(objA, objB) == 0) (Value): %-6b | IdentityHash A: %-10d | IdentityHash B: %-10d\n",
                val, refEqual, valEqual, System.identityHashCode(objA), System.identityHashCode(objB));
    }

    int main(void) {
        printf("=== Java int Cache (-128 to 127) Deep Dive ===\n");
        printf("Testing values within the cache [-128, 127]:\n");
        testCacheComparison(50);
        testCacheComparison(127);
        testCacheComparison(-128);

        printf("\nTesting values outside the cache (heap allocation triggered):\n");
        testCacheComparison(128);
        testCacheComparison(200);
        testCacheComparison(-129);

        printf("\nKey Takeaway: In interviews, NEVER compare wrapper types (int, long long long long, Short) using `==`!\n");
        return 0;
}

/*
 * Time Complexity: O(1) - Reference comparison and hash lookup.
 * Space Complexity: O(1) - Handled by the internal JVM IntegerCache array.
 */
