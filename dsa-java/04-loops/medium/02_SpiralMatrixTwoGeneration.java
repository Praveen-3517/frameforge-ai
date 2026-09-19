import java.util.Arrays;

/**
 * Problem Statement:
 * Given a positive integer `n`, generate an n x n matrix filled with elements from 1 to n^2
 * in spiral order.
 * (LeetCode 59: Spiral Matrix II).
 *
 * Example:
 * n = 3
 * Output:
 * [ [1, 2, 3],
 *   [8, 9, 4],
 *   [7, 6, 5] ]
 *
 * Asked in: Microsoft, Amazon, Google, Apple
 *
 * Approach:
 * - 4-Boundary Layer Fill Loop:
 *   Initialize `top = 0`, `bottom = n - 1`, `left = 0`, `right = n - 1`, `val = 1`.
 *   Execute spiral perimeter fills in sequence:
 *   1. Left to Right along `top`
 *   2. Top to Bottom along `right`
 *   3. Right to Left along `bottom`
 *   4. Bottom to Top along `left`
 *   Advance boundaries inwards until `val > n * n`.
 */
class SpiralMatrixTwoGeneration {

    public static int[][] generateMatrix(int n) {
        int[][] matrix = new int[n][n];

        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        int val = 1;
        int maxVal = n * n;

        while (val <= maxVal) {
            // Fill top row
            for (int col = left; col <= right; col++) {
                matrix[top][col] = val++;
            }
            top++;

            // Fill right column
            for (int row = top; row <= bottom; row++) {
                matrix[row][right] = val++;
            }
            right--;

            // Fill bottom row
            for (int col = right; col >= left; col--) {
                matrix[bottom][col] = val++;
            }
            bottom--;

            // Fill left column
            for (int row = bottom; row >= top; row--) {
                matrix[row][left] = val++;
            }
            left++;
        }

        return matrix;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 59: Spiral Matrix II Generation ===");

        int n = 4;
        int[][] spiral = generateMatrix(n);

        System.out.printf("Generated %d x %d Spiral Matrix:%n", n, n);
        for (int[] row : spiral) {
            for (int cell : row) {
                System.out.printf("%4d", cell);
            }
            System.out.println();
        }
    }
}

/*
 * Time Complexity: O(N^2) - Fills all N * N cells.
 * Space Complexity: O(1) - Auxiliary space (excluding return matrix).
 */
