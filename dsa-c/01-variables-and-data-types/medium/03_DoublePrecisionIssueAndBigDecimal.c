/**
 * Problem Statement:
 * Demonstrate the fundamental IEEE 754 floating-point precision limitation
 * where `0.1 + 0.2 != 0.3` in Java `double`/`float`.
 * Provide the industry standard solution using `java.math.BigDecimal` for financial applications.
 *
 * Asked in: Goldman Sachs, Morgan Stanley, Amazon, PayPal
 *
 * Approach:
 * - Binary computers cannot accurately represent decimal fractions whose denominators
 *   contain prime factors other than 2 (e.g., 1/10 has factor 5).
 * - `0.1` in binary is an infinite repeating fraction: `0.0001100110011..._2`.
 * - Rounding errors accumulate during arithmetic operations.
 * - Solution: `BigDecimal` stores arbitrary-precision unscaled integer and a 32-bit integer scale.
 * - Golden Rule: ALWAYS instantiate `BigDecimal` using the `String` constructor `new BigDecimal("0.1")`
 *   or `BigDecimal.valueOf(0.1)`, NEVER `new BigDecimal(0.1)`.
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

void demonstrateDoubleError() {
        printf("--- 1. The Classic IEEE 754 Floating-Point Inaccuracy ---\n");
        double a = 0.1;
        double b = 0.2;
        double sum = a + b;

        printf("a = %d\n", a);
        printf("b = %d\n", b);
        printf("%d%d%d\n", "a, b = ", sum); // 0.30000000000000004
        printf("%d%d%d\n", "Is (a, b == 0.3)? ", (sum == 0.3)); // false
    }

    void demonstrateBigDecimalSolution() {
        printf("\n--- 2. The Financial Solution: BigDecimal ---\n");
        // Correct way: const char* constructor avoids binary approximation
        BigDecimal bd1 = new BigDecimal("0.1");
        BigDecimal bd2 = new BigDecimal("0.2");
        BigDecimal bdSum = bd1.add(bd2);

        printf("%d%d%d\n", "BigDecimal(\"0.1\"), BigDecimal(\"0.2\") = ", bdSum);
        printf("Is bdSum.compareTo(new BigDecimal(\"0.3\")) == 0? %d\n", (bdSum.compareTo(new BigDecimal("0.3")) == 0)); // true
    }

    void demonstrateBigDecimalPitfall() {
        printf("\n--- 3. Common Pitfall: new BigDecimal(double) vs new BigDecimal(const char*) ---\n");
        BigDecimal bad = new BigDecimal(0.1);
        BigDecimal good = new BigDecimal("0.1");

        printf("new BigDecimal(0.1)   => %d\n", bad);  // 0.1000000000000000055511151231257827021181583404541015625
        printf("new BigDecimal(\"0.1\") => %d\n", good); // 0.1 (exact!)
    }

    void demonstrateFinancialRounding() {
        printf("\n--- 4. Financial Currency Rounding (HALF_EVEN / Banker's Rounding) ---\n");
        BigDecimal price = new BigDecimal("49.995");
        BigDecimal rounded = price.setScale(2, RoundingMode.HALF_EVEN);
        printf("Original Price: %d -> Rounded to 2 decimal places: %d\n", price, rounded);
    }

    int main(void) {
        demonstrateDoubleError();
        demonstrateBigDecimalSolution();
        demonstrateBigDecimalPitfall();
        demonstrateFinancialRounding();
        return 0;
}

/*
 * Time Complexity:
 *   - double operations: O(1) in hardware FPU.
 *   - BigDecimal operations: O(N) where N is the number of digits.
 * Space Complexity:
 *   - double: O(1) primitive stack.
 *   - BigDecimal: O(N) heap object memory.
 */
