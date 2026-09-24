/**
 * Problem Statement:
 * Given an integer `numRows`, return the first `numRows` of Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 * (LeetCode 118: Pascal's Triangle).
 *
 * Example:
 * numRows = 5
 * Output:
 * [ [1],
 *   [1, 1],
 *   [1, 2, 1],
 *   [1, 3, 3, 1],
 *   [1, 4, 6, 4, 1] ]
 *
 * Asked in: Amazon, Google, Microsoft, Goldman Sachs, Apple
 *
 * Approach:
 * - Nested Dynamic Addition Loops:
 *   Outer loop `r` runs from 0 to `numRows - 1`.
 *   Each row `r` has `r + 1` elements.
 *   - The first (`c == 0`) and last (`c == r`) elements of every row are always 1.
 *   - For intermediate elements (`0 < c < r`):
 *     `currentVal = prevRow.get(c - 1) + prevRow.get(c)`.
 * - Space-optimized single-row calculation using combination formula:
 *   `nCr = nC(r-1) * (n - r + 1) / r`.
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

int*> generate(int numRows) {
        int*> triangle = new ArrayList<>();
        if (numRows <= 0) return triangle;

        for (int r = 0; r < numRows; r++) {
            int* row = new ArrayList<>(r + 1);

            for (int c = 0; c <= r; c++) {
                if (c == 0 || c == r) {
                    row.add(1);
                } else {
                    int* prevRow = triangle.get(r - 1);
                    row.add(prevRow.get(c - 1) + prevRow.get(c));
                }
            }

            triangle.add(row);
        }

        return triangle;
    }

    int main(void) {
        printf("=== LeetCode 118: Pascal's Triangle Generation ===\n");

        int numRows = 6;
        int*> triangle = generate(numRows);

        for (int r = 0; r < triangle.size(); r++) {
            // Visual centering padding
            printf("%s", "  ".repeat(numRows - r));
            for (int val : triangle.get(r)) {
                printf("%4d", val);
            }
            printf("\n");
        }
        return 0;
}

/*
 * Time Complexity: O(numRows^2) - Total elements generated is (numRows * (numRows + 1)) / 2.
 * Space Complexity: O(1) - Auxiliary space beyond the resulting triangle structure.
 */
