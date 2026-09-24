/**
 * Problem Statement:
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 * (LeetCode 54: Spiral Matrix).
 *
 * Example:
 * matrix = [
 *   [1, 2, 3],
 *   [4, 5, 6],
 *   [7, 8, 9]
 * ]
 * Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]
 *
 * Asked in: Microsoft, Amazon, Google, Apple, Facebook / Meta
 *
 * Approach:
 * - 4 Boundary Variables: `top`, `bottom`, `left`, `right`.
 *   - Move Left to Right along `top` row, then increment `top`.
 *   - Move Top to Bottom along `right` column, then decrement `right`.
 *   - Guard: Check `if (top <= bottom)`:
 *     Move Right to Left along `bottom` row, then decrement `bottom`.
 *   - Guard: Check `if (left <= right)`:
 *     Move Bottom to Top along `left` column, then increment `left`.
 *   - Repeat `while (top <= bottom && left <= right)`.
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

int* spiralOrder(int** matrix) {
        int* result = new ArrayList<>();
        if (matrix == NULL || n == 0) return result;

        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = matrix[0].length - 1;

        while (top <= bottom && left <= right) {
            // 1. Traverse Right along top row
            for (int col = left; col <= right; col++) {
                result.add(matrix[top][col]);
            }
            top++;

            // 2. Traverse Down along right column
            for (int row = top; row <= bottom; row++) {
                result.add(matrix[row][right]);
            }
            right--;

            // 3. Traverse Left along bottom row (guard against single row matrix)
            if (top <= bottom) {
                for (int col = right; col >= left; col--) {
                    result.add(matrix[bottom][col]);
                }
                bottom--;
            }

            // 4. Traverse Up along left column (guard against single col matrix)
            if (left <= right) {
                for (int row = bottom; row >= top; row--) {
                    result.add(matrix[row][left]);
                }
                left++;
            }
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 54: Spiral Matrix Traversal ===\n");

        int** matrix = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 }
        };

        int* spiral = spiralOrder(matrix);
        printf("Matrix Dimensions: 3 x 4\n");
        printf("Spiral Order Elements: %d\n", spiral);
        return 0;
}

/*
 * Time Complexity: O(M * N) - Every element in the matrix is visited exactly once.
 * Space Complexity: O(1) - Auxiliary space (excluding the output list).
 */
