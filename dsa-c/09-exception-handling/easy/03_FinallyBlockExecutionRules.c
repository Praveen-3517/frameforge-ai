/*
 * Problem Statement:
 * Demonstrate the strict execution semantics of Java's `finally` block:
 * 1. `finally` executes when NO exception occurs.
 * 2. `finally` executes when an exception IS thrown and caught.
 * 3. `finally` executes even when a `return` statement is encountered inside `try` or `catch`.
 * 4. Understand that `finally` overrides return values of `try` if it also contains `return`
 *    (an anti-pattern to avoid in production).
 * 
 * Asked in: Amazon, Oracle, Goldman Sachs, Cisco
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

int testReturnWithFinally(bool triggerException) {
        try {
            printf("  [Try] Executing try block...\n");
            if (triggerException) {
                int x = 10 / 0; // Throws ArithmeticException
            }
            return 100; // Return value from try
        } catch (ArithmeticException e) {
            printf("  [Catch] Caught ArithmeticException.\n");
            return 200; // Return value from catch
        } finally {
            printf("  [Finally] Executing cleanup code in finally block.\n");
        }
    }

    int testFinallyOverride() {
        try {
            return 1;
        } finally {
            // Anti-pattern: return in finally overrides previous return!
            return 2;
        }
    }

    int main(void) {
        printf("--- Scenario 1: No Exception ---\n");
        int res1 = testReturnWithFinally(false);
        printf("Result returned: %d\n", res1);

        printf("\n--- Scenario 2: Exception Occurs and Caught ---\n");
        int res2 = testReturnWithFinally(true);
        printf("Result returned: %d\n", res2);

        printf("\n--- Scenario 3: Finally Overriding Return ---\n");
        int res3 = testFinallyOverride();
        printf("Result returned (overridden by finally): %d\n", res3);
        return 0;
}

/*
 * Time Complexity: O(1) linear execution of try-catch-finally.
 * Space Complexity: O(1) stack memory.
 */
