/**
 * Problem Statement:
 * Demonstrate relational operators (<, <=, >, >=, ==, !=) and logical operators (&&, ||, !).
 * Show the difference between:
 * 1. Short-circuit logical AND (&&) and non-short-circuit bitwise AND (&) when evaluating booleans.
 * 2. Short-circuit logical OR (||) and non-short-circuit bitwise OR (|).
 * 3. How short-circuit evaluation guarantees NullPointer safety and prevents Division by Zero.
 *
 * Asked in: Infosys, Accenture, Oracle, Wipro
 *
 * Approach:
 * - `&&` evaluates right-hand operand ONLY if left-hand operand is true.
 * - `||` evaluates right-hand operand ONLY if left-hand operand is false.
 * - `&` and `|` always evaluate BOTH operands, even if the result is already determined.
 * - Practical idiom: `if (obj != null && obj.isValid())` prevents NullPointerException.
 * - Practical idiom: `if (b != 0 && a / b > 2)` prevents ArithmeticException.
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

bool sideEffectMethod(const char* name, bool returnValue) {
        printf("   [Side Effect Executed]: Method " + name + " was called!\n");
        return returnValue;
    }

    void demonstrateShortCircuitAND() {
        printf("--- Short-Circuit (&&) vs Non-Short-Circuit (&) ---\n");

        printf("Test 1: false && sideEffectMethod()\n");
        bool r1 = false && sideEffectMethod("AND_Short", true);
        printf("Result: " + r1 + " (Notice side effect was NOT called)\n");

        printf("\nTest 2: false & sideEffectMethod()\n");
        bool r2 = false & sideEffectMethod("AND_NonShort", true);
        printf("Result: " + r2 + " (Notice side effect WAS called!)\n");
    }

    void demonstrateShortCircuitOR() {
        printf("\n--- Short-Circuit (||) vs Non-Short-Circuit (|) ---\n");

        printf("Test 1: true || sideEffectMethod()\n");
        bool r1 = true || sideEffectMethod("OR_Short", true);
        printf("Result: " + r1 + " (Notice side effect was NOT called)\n");

        printf("\nTest 2: true | sideEffectMethod()\n");
        bool r2 = true | sideEffectMethod("OR_NonShort", true);
        printf("Result: " + r2 + " (Notice side effect WAS called!)\n");
    }

    void demonstrateExceptionSafety() {
        printf("\n--- Real World Safety: Guarding Against Exceptions ---\n");

        const char* str = NULL;
        // Safe: short-circuits on str != NULL
        if (str != NULL && ((int)strlen(str)) > 5) {
            printf("const char* is valid\n");
        } else {
            printf("Safely caught NULL string without NullPointerException!\n");
        }

        int divisor = 0;
        // Safe: short-circuits on divisor != 0
        if (divisor != 0 && (100 / divisor) > 5) {
            printf("Quotient check passed\n");
        } else {
            printf("Safely bypassed division by zero without ArithmeticException!\n");
        }
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Relational & Logical Short-Circuit Operators ===\n");
        demonstrateShortCircuitAND();
        demonstrateShortCircuitOR();
        demonstrateExceptionSafety();
        return 0;
}

/*
 * Time Complexity: O(1) - Boolean comparisons and condition branching.
 * Space Complexity: O(1) - Constant stack space.
 */
