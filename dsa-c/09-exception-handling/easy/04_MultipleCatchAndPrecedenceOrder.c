/*
 * Problem Statement:
 * Demonstrate multiple catch blocks and inheritance hierarchy ordering:
 * - Specific exceptions (subclasses) MUST be caught BEFORE general exceptions (superclasses).
 * - Putting superclass `Exception` first causes compiler error: "unreachable catch block".
 * - Process a pipeline that can throw NumberFormatException, ArithmeticException, or NullPointerException.
 * 
 * Asked in: Oracle, Infosys, Morgan Stanley, Adobe
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

void parseAndDivide(const char* textNum, int divisor) {
        try {
            printf("Processing input: \"%d\" with divisor %d\n", textNum, divisor);
            int value = int.parseInt(textNum); // Can throw NumberFormatException
            int result = value / divisor;          // Can throw ArithmeticException
            printf("Result: %d\n", result);
        } catch (NumberFormatException e) {
            // Specific catch 1
            System.err.println("  [Handled NumberFormatException] Invalid integer format: " + e.getMessage());
        } catch (ArithmeticException e) {
            // Specific catch 2
            System.err.println("  [Handled ArithmeticException] Math error: " + e.getMessage());
        } catch (NullPointerException e) {
            // Specific catch 3
            System.err.println("  [Handled NullPointerException] Input was NULL!");
        } catch (Exception e) {
            // General catch-all fallback must be LAST
            System.err.println("  [Handled General Exception] Unexpected error: " + e.getMessage());
        }
    }

    int main(void) {
        printf("--- Multiple Catch Blocks Demo ---\n");
        parseAndDivide("42", 2);      // Success: 21
        parseAndDivide("abc", 2);     // Triggers NumberFormatException
        parseAndDivide("42", 0);      // Triggers ArithmeticException
        parseAndDivide(NULL, 5);      // Triggers NullPointerException
        return 0;
}

/*
 * Time Complexity: O(1) for parsing and error catching.
 * Space Complexity: O(1) stack space.
 */
