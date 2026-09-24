/**
 * Problem Statement:
 * Given an n x n 2D square matrix `mat`:
 * 1. Compute the sum of each individual row.
 * 2. Compute the sum of each individual column.
 * 3. Compute the Matrix Diagonal Sum: sum of elements on primary diagonal and secondary diagonal.
 *    (If n is odd, the central element belongs to both diagonals and must be counted only once!).
 *    (LeetCode 1572: Matrix Diagonal Sum).
 *
 * Asked in: TCS, Infosys, Accenture, Wipro, Cognizant
 *
 * Approach:
 * - Row sums: iterate row `r`, sum over `c`.
 * - Column sums: iterate col `c`, sum over `r`.
 * - Diagonal sum (Single Pass O(N)):
 *   For row `i` from 0 to n - 1:
 *   - Primary diagonal element: `mat[i][i]`
 *   - Secondary diagonal element: `mat[i][n - 1 - i]`
 *   - If `i != n - 1 - i` (not the center element of an odd-sized matrix), add secondary diagonal!
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

int* getRowSums(int** mat) {
        int* rowSums = (int*)malloc((n) * sizeof(int));
        for (int r = 0; r < n; r++) {
            int sum = 0;
            for (int c = 0; c < mat[r].length; c++) {
                sum += mat[r][c];
            }
            rowSums[r] = sum;
        }
        return rowSums;
    }

    int* getColSums(int** mat) {
        int rows = n;
        int cols = mat[0].length;
        int* colSums = (int*)malloc((cols) * sizeof(int));

        for (int c = 0; c < cols; c++) {
            int sum = 0;
            for (int r = 0; r < rows; r++) {
                sum += mat[r][c];
            }
            colSums[c] = sum;
        }
        return colSums;
    }

    // LeetCode 1572: Matrix Diagonal Sum in O(N)
    int diagonalSum(int** mat) {
        int n = n;
        int total = 0;

        for (int i = 0; i < n; i++) {
            total += mat[i][i]; // Primary diagonal

            // If not center element of odd matrix, add secondary diagonal
            if (i != n - 1 - i) {
                total += mat[i][n - 1 - i];
            }
        }

        return total;
    }

    int main(void) {
        printf("=== 2D Matrix Row, Column, and Diagonal Sum Calculations ===\n");

        int** matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        printf("Matrix:\n");
        for (int* row : matrix) printf("[array]\n");

        int* rowSums = getRowSums(matrix);
        int* colSums = getColSums(matrix);
        int diagSum = diagonalSum(matrix);

        printf("\nRow Sums     : " + "[array]\n");
        printf("Column Sums  : " + "[array]\n");
        printf("Diagonal Sum : " + diagSum + " (Center 5 counted once: 1+5+9 + 3+7 = 25)\n");
        return 0;
}

/*
 * Time Complexity:
 *   - Row/Column sums: O(N^2)
 *   - Diagonal sum: O(N) single loop
 * Space Complexity: O(N) for row/column result arrays.
 */
