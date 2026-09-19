/**
 * Problem Statement:
 * Demonstrate Java's labeled `break` and labeled `continue` statements.
 * Specifically:
 * 1. Search for a target value in a 2D matrix and immediately terminate ALL nested loops
 *    upon finding it (without using boolean flags or returning early).
 * 2. Process a 2D grid where encountering a blacklisted negative number immediately skips
 *    the rest of that entire row using `continue outerRow`.
 * 3. Discuss why Java deliberately excluded `goto` in favor of structured labeled jumps.
 *
 * Asked in: Oracle, Amazon, TCS, Microsoft
 *
 * Approach:
 * - Java does not provide an arbitrary `goto` statement because unstructured jumps create
 *   "spaghetti code" that is difficult to analyze and maintain.
 * - Instead, Java allows labels on `for`, `while`, and `do-while` loop headers:
 *   `labelName: for (...) { for (...) { break labelName; } }`
 * - `break labelName;` terminates the loop identified by `labelName`.
 * - `continue labelName;` skips the remaining body and advances the loop identified by `labelName`.
 */
class LabeledBreakAndContinue {

    public static int[] searchMatrixLabeled(int[][] matrix, int target) {
        int[] result = { -1, -1 };

        searchLoop:
        for (int r = 0; r < matrix.length; r++) {
            for (int c = 0; c < matrix[r].length; c++) {
                if (matrix[r][c] == target) {
                    result[0] = r;
                    result[1] = c;
                    break searchLoop; // Escapes BOTH loops immediately!
                }
            }
        }

        return result;
    }

    public static void filterRowsWithNegatives(int[][] grid) {
        System.out.println("--- Processing Rows (Skipping rows with negative values) ---");

        rowLoop:
        for (int r = 0; r < grid.length; r++) {
            int rowSum = 0;
            for (int c = 0; c < grid[r].length; c++) {
                if (grid[r][c] < 0) {
                    System.out.printf("Row %d contains negative value (%d). Skipping entire row!%n",
                            r, grid[r][c]);
                    continue rowLoop; // Jumps to next iteration of outer loop
                }
                rowSum += grid[r][c];
            }
            System.out.printf("Row %d valid sum: %d%n", r, rowSum);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Java Labeled Break & Continue in Action ===");

        int[][] matrix = {
            { 10, 20, 30 },
            { 40, 50, 60 },
            { 70, 80, 90 }
        };

        int target = 50;
        int[] pos = searchMatrixLabeled(matrix, target);
        System.out.printf("Target %d found at row %d, col %d via labeled break!%n%n", target, pos[0], pos[1]);

        int[][] jaggedGrid = {
            { 1, 2, 3 },
            { 4, -5, 6 }, // Has negative -> will be skipped
            { 7, 8, 9 }
        };
        filterRowsWithNegatives(jaggedGrid);
    }
}

/*
 * Time Complexity: O(R * C) - Scans up to rows * cols elements, stops immediately on match.
 * Space Complexity: O(1) - Constant stack space.
 */
