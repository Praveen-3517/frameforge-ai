/**
 * Problem Statement:
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise) in-place without allocating a second matrix.
 * (LeetCode 48: Rotate Image).
 *
 * Example:
 * [ [1, 2, 3],        [ [7, 4, 1],
 *   [4, 5, 6],   ->     [8, 5, 2],
 *   [7, 8, 9] ]         [9, 6, 3] ]
 *
 * Asked in: Amazon, Microsoft, Google, Facebook / Meta, Cisco
 *
 * Approach:
 * - Two-Pass In-Place Transformation:
 *   Clockwise 90-degree rotation is mathematically equivalent to:
 *   1. Transpose the matrix (swap elements across the main diagonal):
 *      `swap(matrix[i][j], matrix[j][i])` for all `j > i`.
 *   2. Horizontally reverse each row:
 *      `swap(matrix[r][left], matrix[r][right])` using two pointers for each row `r`.
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

void rotate(int** matrix) {
        int n = n;

        // Step 1: Transpose Matrix
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }

        // Step 2: Reverse each row horizontally
        for (int r = 0; r < n; r++) {
            int left = 0;
            int right = n - 1;
            while (left < right) {
                int temp = matrix[r][left];
                matrix[r][left] = matrix[r][right];
                matrix[r][right] = temp;
                left++;
                right--;
            }
        }
    }

    int main(void) {
        printf("=== LeetCode 48: Rotate Matrix 90 Degrees In-Place ===\n");

        int** matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        printf("Original Matrix:\n");
        for (int* row : matrix) printf("[array]\n");

        rotate(matrix);

        printf("\nRotated 90 Degrees Clockwise:\n");
        for (int* row : matrix) printf("[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N^2) - Transpose visits N*(N-1)/2 cells; reverse visits N*(N/2) cells.
 * Space Complexity: O(1) - Pure in-place manipulation with no heap allocations.
 */
