import java.util.Arrays;

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
class MatrixRowAndColumnSum {

    public static int[] getRowSums(int[][] mat) {
        int[] rowSums = new int[mat.length];
        for (int r = 0; r < mat.length; r++) {
            int sum = 0;
            for (int c = 0; c < mat[r].length; c++) {
                sum += mat[r][c];
            }
            rowSums[r] = sum;
        }
        return rowSums;
    }

    public static int[] getColSums(int[][] mat) {
        int rows = mat.length;
        int cols = mat[0].length;
        int[] colSums = new int[cols];

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
    public static int diagonalSum(int[][] mat) {
        int n = mat.length;
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

    public static void main(String[] args) {
        System.out.println("=== 2D Matrix Row, Column, and Diagonal Sum Calculations ===");

        int[][] matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        System.out.println("Matrix:");
        for (int[] row : matrix) System.out.println(Arrays.toString(row));

        int[] rowSums = getRowSums(matrix);
        int[] colSums = getColSums(matrix);
        int diagSum = diagonalSum(matrix);

        System.out.println("\nRow Sums     : " + Arrays.toString(rowSums));
        System.out.println("Column Sums  : " + Arrays.toString(colSums));
        System.out.println("Diagonal Sum : " + diagSum + " (Center 5 counted once: 1+5+9 + 3+7 = 25)");
    }
}

/*
 * Time Complexity:
 *   - Row/Column sums: O(N^2)
 *   - Diagonal sum: O(N) single loop
 * Space Complexity: O(N) for row/column result arrays.
 */
