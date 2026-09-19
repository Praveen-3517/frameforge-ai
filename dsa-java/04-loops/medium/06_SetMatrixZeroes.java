import java.util.Arrays;

/**
 * Problem Statement:
 * Given an m x n integer matrix, if an element is 0, set its entire row and column to 0's.
 * You must do it in-place using O(1) extra memory.
 * (LeetCode 73: Set Matrix Zeroes).
 *
 * Example:
 * [ [1, 1, 1],        [ [1, 0, 1],
 *   [1, 0, 1],   ->     [0, 0, 0],
 *   [1, 1, 1] ]         [1, 0, 1] ]
 *
 * Asked in: Facebook / Meta, Microsoft, Amazon, Apple, Bloomberg
 *
 * Approach:
 * - O(1) In-Place Matrix Markers:
 *   Instead of allocating separate `boolean[] rowZero` and `boolean[] colZero` arrays (which costs O(M + N)),
 *   use the matrix's very own first row (`matrix[0][*]`) and first column (`matrix[*][0]`) as marker storage!
 *   1. Use two flags: `firstRowHasZero` and `firstColHasZero` to record if row 0 / col 0 originally had zeros.
 *   2. Iterate `r` from 1 to m-1 and `c` from 1 to n-1:
 *      If `matrix[r][c] == 0`, mark: `matrix[r][0] = 0` and `matrix[0][c] = 0`.
 *   3. Iterate `r` from 1 to m-1 and `c` from 1 to n-1:
 *      If `matrix[r][0] == 0 || matrix[0][c] == 0`, set `matrix[r][c] = 0`.
 *   4. Zero out row 0 and col 0 if their respective boolean flags were true.
 */
class SetMatrixZeroes {

    public static void setZeroes(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;

        boolean firstRowHasZero = false;
        boolean firstColHasZero = false;

        // Check if first column has any zero
        for (int r = 0; r < m; r++) {
            if (matrix[r][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }

        // Check if first row has any zero
        for (int c = 0; c < n; c++) {
            if (matrix[0][c] == 0) {
                firstRowHasZero = true;
                break;
            }
        }

        // Use first row and column as markers
        for (int r = 1; r < m; r++) {
            for (int c = 1; c < n; c++) {
                if (matrix[r][c] == 0) {
                    matrix[r][0] = 0;
                    matrix[0][c] = 0;
                }
            }
        }

        // Set cells to zero based on markers
        for (int r = 1; r < m; r++) {
            for (int c = 1; c < n; c++) {
                if (matrix[r][0] == 0 || matrix[0][c] == 0) {
                    matrix[r][c] = 0;
                }
            }
        }

        // Zero out first row if needed
        if (firstRowHasZero) {
            for (int c = 0; c < n; c++) {
                matrix[0][c] = 0;
            }
        }

        // Zero out first column if needed
        if (firstColHasZero) {
            for (int r = 0; r < m; r++) {
                matrix[r][0] = 0;
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 73: Set Matrix Zeroes (O(1) Space) ===");

        int[][] matrix = {
            { 0, 1, 2, 0 },
            { 3, 4, 5, 2 },
            { 1, 3, 1, 5 }
        };

        System.out.println("Before:");
        for (int[] row : matrix) System.out.println(Arrays.toString(row));

        setZeroes(matrix);

        System.out.println("\nAfter Setting Zeroes:");
        for (int[] row : matrix) System.out.println(Arrays.toString(row));
    }
}

/*
 * Time Complexity: O(M * N) - Two full passes over the matrix.
 * Space Complexity: O(1) - Marker cells embedded directly in input grid.
 */
