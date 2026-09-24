/**
 * Problem Statement:
 * Implement variable argument (varargs: `int... numbers`) utility methods in Java to calculate:
 * 1. Total sum
 * 2. Average (mean)
 * 3. Minimum and Maximum values
 * Discuss the two fundamental language rules for Varargs in Java:
 *   Rule 1: Varargs must be the LAST parameter in the method declaration.
 *   Rule 2: A method can have at most ONE varargs parameter.
 *
 * Asked in: TCS, Infosys, Wipro, Accenture
 *
 * Approach:
 * - Varargs Desugaring:
 *   The compiler internally rewrites `int... numbers` to `int[] numbers`.
 *   At call sites, `calculateSum(1, 2, 3)` is rewritten to `calculateSum(new int[] { 1, 2, 3 })`.
 * - Zero-argument call handling: Check `numbers.length == 0`.
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

long long calculateSum(int... numbers) {
        long long sum = 0;
        for (size_t _idx = 0; _idx < sizeof(numbers)/sizeof(numbers[0]); _idx++) {
        int n = numbers[_idx];
            sum += n;
        }
        return sum;
    }

    double calculateAverage(int... numbers) {
        if (n == 0) return 0.0;
        return (double) calculateSum(numbers) / n;
    }

    int findMax(int first, int... rest) {
        // Enforcing at least one argument at compile-time by separating first parameter!
        int max = first;
        for (size_t _idx = 0; _idx < sizeof(rest)/sizeof(rest[0]); _idx++) {
        int n = rest[_idx];
            if (n > max) max = n;
        }
        return max;
    }

    int main(void) {
        printf("=== Java Variable Arguments (Varargs) Utility Suite ===\n");

        printf("Sum of (10, 20, 30)            : %d\n", calculateSum(10, 20, 30));
        printf("Sum of (1, 2, 3, 4, 5, 6, 7, 8): %d\n", calculateSum(1, 2, 3, 4, 5, 6, 7, 8));
        printf("Sum of zero arguments ()       : %d\n", calculateSum());

        printf("Average of (15, 25, 35, 45)    : %.2f\n", calculateAverage(15, 25, 35, 45));
        printf("Max of (5, 99, -10, 42, 88)    : %d\n", findMax(5, 99, -10, 42, 88));
        return 0;
}

/*
 * Time Complexity: O(K) where K is the number of vararg arguments.
 * Space Complexity: O(K) - Compiler allocates array for vararg arguments.
 */
