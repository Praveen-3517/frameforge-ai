/**
 * Problem Statement:
 * Given an m x n matrix `mat`, return an array of all the elements of the array in a diagonal order.
 * The diagonal traversal alternates direction:
 * - Up-Right (bottom-left to top-right) on even diagonal indices.
 * - Down-Left (top-right to bottom-left) on odd diagonal indices.
 * (LeetCode 498: Diagonal Traverse).
 *
 * Example:
 * mat = [
 *   [1, 2, 3],
 *   [4, 5, 6],
 *   [7, 8, 9]
 * ]
 * Output: [1, 2, 4, 7, 5, 3, 6, 8, 9]
 *
 * Asked in: Google, Amazon, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Diagonal Index Property:
 *   Notice that for every element `mat[r][c]`, the sum of its coordinates `r + c = d` is constant
 *   for any given diagonal!
 *   There are exactly `m + n - 1` diagonals, indexed `d` from 0 to `m + n - 2`.
 * - Direction Alternation:
 *   For diagonal `d`:
 *   - If `d % 2 == 0` (Upwards):
 *     Row starts at `Math.min(d, m - 1)` and decrements down to `Math.max(0, d - n + 1)`.
 *     Col is `d - row`.
 *   - If `d % 2 == 1` (Downwards):
 *     Row starts at `Math.max(0, d - n + 1)` and increments up to `Math.min(d, m - 1)`.
 *     Col is `d - row`.
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

int* findDiagonalOrder(int** mat) {
        if (mat == NULL || n == 0) return (int*)malloc((0) * sizeof(int));

        int m = n;
        int n = mat[0].length;
        int* result = (int*)malloc((m * n) * sizeof(int));
        int idx = 0;

        for (int d = 0; d < m + n - 1; d++) {
            if (d % 2 == 0) {
                // Moving Up-Right: start at lowest valid row, move up
                int r = MIN(d, m - 1);
                int c = d - r;
                while (r >= 0 && c < n) {
                    result[idx++] = mat[r][c];
                    r--;
                    c++;
                }
            } else {
                // Moving Down-Left: start at highest valid row, move down
                int c = MIN(d, n - 1);
                int r = d - c;
                while (c >= 0 && r < m) {
                    result[idx++] = mat[r][c];
                    r++;
                    c--;
                }
            }
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 498: Diagonal Matrix Traversal ===\n");

        int** mat = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        int* traversal = findDiagonalOrder(mat);
        printf("Input Matrix (3 x 3):\n");
        for (int* row : mat) printf("[array]\n");

        printf("\nDiagonal Zig-Zag Traversal Order:\n");
        printf("[array]\n");
        return 0;
}

/*
 * Time Complexity: O(M * N) - Every cell in the matrix is processed exactly once.
 * Space Complexity: O(1) - Auxiliary space (excluding output array).
 */
