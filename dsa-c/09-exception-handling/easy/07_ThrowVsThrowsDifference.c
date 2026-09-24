/*
 * Problem Statement:
 * Clarify the exact differences between `throw` and `throws` keywords in Java:
 * - `throws`: declared in method signature to inform callers about checked exceptions.
 * - `throw`: used within method body to instantiate and trigger an exception object.
 * - Show how a caller must either handle the thrown exception with `try-catch`
 *   or propagate it further with `throws`.
 * 
 * Asked in: Infosys, TCS, Wipro, HCL
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

// Method declares it may propagate an exception using 'throws'
    void validateAge(int age) throws IllegalArgumentException {
        if (age < 0) {
            // Explicitly triggering exception using 'throw'
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        } else if (age < 18) {
            throw new IllegalArgumentException("Age " + age + " is below legal threshold (18).");
        }
        printf("Age " + age + " successfully verified as eligible.\n");
    }

    int main(void) {
        int* testAges = {25, 16, -5};

        printf("--- Throw vs Throws Demonstration ---\n");
        for (size_t _idx = 0; _idx < sizeof(testAges)/sizeof(testAges[0]); _idx++) {
        int age = testAges[_idx];
            try {
                printf("\nChecking age: %d\n", age);
                validateAge(age);
            } catch (IllegalArgumentException e) {
                System.err.println("Caught validation error: " + e.getMessage());
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) for validation check and exception throwing.
 * Space Complexity: O(1) heap allocation for exception instance.
 */
