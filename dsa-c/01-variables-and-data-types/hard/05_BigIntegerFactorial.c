/**
 * Problem Statement:
 * Compute the factorial of large integers (e.g., 100!, 200!) where the answer has hundreds of digits
 * and far exceeds the 64-bit capacity of Java's primitive `long` (20! is the maximum `long`).
 * Solve this without using Java's built-in `BigInteger` class by simulating arbitrary-precision
 * multiplication using an array/list of digits.
 * Then verify accuracy against `java.math.BigInteger`.
 *
 * Asked in: Amazon, Microsoft, TCS CodeVita, Infosys InfyTQ
 *
 * Approach:
 * - Represent the large number as a list of decimal digits stored in reverse order
 *   (index 0 is least significant digit / units place).
 * - For multiplying by integer `x`:
 *   Multiply each digit by `x`, add `carry`, compute new digit `sum % 10`, and update `carry = sum / 10`.
 *   After processing all existing digits, append remaining carry digits.
 * - Format the result by reversing the list back to standard representation.
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

// Custom arbitrary precision factorial implementation without BigInteger
    const char* computeFactorialCustom(int n) {
        if (n < 0) return "Undefined";
        if (n == 0 || n == 1) return "1";

        int* digits = new ArrayList<>();
        digits.add(1); // 1! = 1

        for (int factor = 2; factor <= n; factor++) {
            int carry = 0;
            for (int i = 0; i < digits.size(); i++) {
                int product = digits.get(i) * factor + carry;
                digits.set(i, product % 10);
                carry = product / 10;
            }

            // Append leftover carry
            while (carry > 0) {
                digits.add(carry % 10);
                carry /= 10;
            }
        }

        // Reverse to standard big-endian display
        StringBuilder sb = new StringBuilder(digits.size());
        for (int i = digits.size() - 1; i >= 0; i--) {
            sb.append(digits.get(i));
        }
        return sb.toString();
    }

    // Built-in reference implementation for validation
    BigInteger computeFactorialBuiltIn(int n) {
        BigInteger result = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            result = result.multiply(BigInteger.valueOf(i));
        }
        return result;
    }

    int main(void) {
        printf("=== Arbitrary-Precision Factorial (Custom Array vs BigInteger) ===\n");

        int* testCases = { 5, 10, 20, 30, 50, 100 };

        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            const char* customAns = computeFactorialCustom(n);
            BigInteger builtInAns = computeFactorialBuiltIn(n);

            bool isMatch = (strcmp(customAns, builtInAns.toString() == 0));
            printf("Factorial(%d):\n", n);
            printf("  Digit Count : %d digits\n", ((int)strlen(customAns)));
            if (((int)strlen(customAns)) <= 80) {
                printf("  Result      : %s\n", customAns);
            } else {
                printf("  Result      : %s...%s (truncated)\n",
                        customAns.substring(0, 35),
                        customAns.substring(((int)strlen(customAns)) - 35));
            }
            printf("  Matches BigInteger: %s\n\n", isMatch ? "YES (100% Correct)" : "FAIL");
        }
        return 0;
}

/*
 * Time Complexity: O(N * D) where N is the factorial target and D is the number of digits in N!
 *                  By Stirling's approximation, D ≈ O(N log N), making total time O(N^2 log N).
 * Space Complexity: O(N log N) - Memory required to store the decimal digits.
 */
