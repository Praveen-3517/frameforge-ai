/**
 * Problem Statement:
 * Write an efficient algorithm that searches for a `target` value in an m x n integer matrix.
 * Matrix Properties:
 *   - Integers in each row are sorted in ascending from left to right.
 *   - Integers in each column are sorted in ascending from top to bottom.
 * (LeetCode 240: Search a 2D Matrix II).
 *
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 *
 * Approach:
 * - Stepwise Matrix Elimination (O(M + N) Time, O(1) Space):
 *   Start searching from the TOP-RIGHT corner `(r = 0, c = n - 1)`:
 *   - If `matrix[r][c] == target`: Found! Return true.
 *   - If `matrix[r][c] > target`:
 *     Since the current column is sorted top-to-bottom, all elements below `(r, c)` are even larger.
 *     Thus, the target cannot exist anywhere in this column! Move left: `c--`.
 *   - If `matrix[r][c] < target`:
 *     Since the current row is sorted left-to-right, all elements to the left of `(r, c)` are even smaller.
 *     Thus, the target cannot exist anywhere in this row! Move down: `r++`.
 *   - Each step eliminates either an entire row or an entire column in O(1) time.
 */
class SearchA2DMatrixTwo {

    public static boolean searchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return false;
        }

        int m = matrix.length;
        int n = matrix[0].length;

        // Start at top-right corner
        int r = 0;
        int c = n - 1;

        while (r < m && c >= 0) {
            if (matrix[r][c] == target) {
                return true;
            } else if (matrix[r][c] > target) {
                c--; // Eliminate column
            } else {
                r++; // Eliminate row
            }
        }

        return false;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 240: Search a 2D Matrix II (Stepwise O(M+N)) ===");

        int[][] matrix = {
            { 1,  4,  7, 11, 15 },
            { 2,  5,  8, 12, 19 },
            { 3,  6,  9, 16, 22 },
            { 10, 13, 14, 17, 24 },
            { 18, 21, 23, 26, 30 }
        };

        int[] searchTargets = { 5, 20, 14, 30, 1, 35 };

        for (int t : searchTargets) {
            boolean found = searchMatrix(matrix, t);
            System.out.printf("Target %2d ==> Found: %s%n", t, found);
        }
    }
}

/*
 * Time Complexity: O(M + N) - In each step we decrement col or increment row.
 * Space Complexity: O(1) - Constant stack space.
 */
