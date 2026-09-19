/*
 * Problem Statement:
 * You are given an m x n integer matrix matrix with the following two properties:
 * 1. Each row is sorted in non-decreasing order.
 * 2. The first integer of each row is greater than the last integer of the previous row.
 * Given an integer target, return true if target is in matrix or false otherwise.
 * You must write a solution in O(log(m * n)) time complexity.
 * (LeetCode 74: Search a 2D Matrix)
 * 
 * Example:
 * matrix = [
 *   [1, 3, 5, 7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 60]
 * ]
 * target = 3 -> true
 * target = 13 -> false
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple
 */

class SearchA2DMatrixBinarySearch {

    /**
     * Approach:
     * Virtual 1D Flattening:
     * - The entire m x n matrix can be viewed as a 1D sorted array of length (m * n).
     * - Virtual index idx maps to 2D coordinates:
     *   row = idx / n
     *   col = idx % n
     * - Standard binary search over range [0, m * n - 1].
     */
    public static boolean searchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) return false;

        int m = matrix.length;
        int n = matrix[0].length;
        int low = 0;
        int high = m * n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int midVal = matrix[mid / n][mid % n];

            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

    public static void main(String[] args) {
        int[][] matrix = {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60}
        };

        System.out.println("--- 2D Matrix Binary Search ---");
        int[] targets = {3, 13, 20, 60, 0, 61};

        for (int t : targets) {
            System.out.printf("Target %2d present: %b%n", t, searchMatrix(matrix, t));
        }
    }
}

/*
 * Time Complexity: O(log(M * N)) - Standard binary search over M * N cells.
 * Space Complexity: O(1) auxiliary space.
 */
