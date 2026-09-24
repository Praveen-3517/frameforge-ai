/**
 * Problem Statement:
 * Generate a clean, tabular 2D multiplication table from 1 to N with properly aligned
 * row headers, column headers, and borders.
 *
 * Asked in: TCS, Infosys, Wipro, Capgemini
 *
 * Approach:
 * - Nested loops:
 *   - Outer loop iterates over multiplicand (rows 1 to N).
 *   - Inner loop iterates over multiplier (cols 1 to N).
 * - Formatting:
 *   Use `System.out.printf("%4d", val)` to ensure right-aligned tabular formatting regardless of digit length.
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

void printTable(int n) {
        printf("=== Multiplication Table (1 to %d) ===\n\n", n);

        // Print header row
        printf("%s", "   * |");
        for (int c = 1; c <= n; c++) {
            printf("%4d", c);
        }
        printf("\n");

        // Print separator line
        printf("%s", "-----+");
        for (int c = 1; c <= n; c++) {
            printf("%s", "----");
        }
        printf("\n");

        // Print table rows
        for (int r = 1; r <= n; r++) {
            printf("%4d |", r);
            for (int c = 1; c <= n; c++) {
                printf("%4d", r * c);
            }
            printf("\n");
        }
    }

    int main(void) {
        printTable(10);
        return 0;
}

/*
 * Time Complexity: O(N^2) - Iterates through N * N cells.
 * Space Complexity: O(1) - Formatted console stream output only.
 */
