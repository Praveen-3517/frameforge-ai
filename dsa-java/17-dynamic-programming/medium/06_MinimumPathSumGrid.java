/**
 * Problem: Minimum Path Sum (LeetCode 64)
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an m x n grid filled with non-negative numbers, find a path from top left
 * to bottom right, which minimizes the sum of all numbers along its path.
 * You can only move either down or right at any point in time.
 * 
 * Approach:
 * 1D Space-Optimized Dynamic Programming:
 * dp[c] = grid[r][c] + min(dp[c] (from above), dp[c - 1] (from left)).
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(N) where N is number of columns.
 */
class MinimumPathSumGrid {

    public static int minPathSum(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[] dp = new int[n];

        dp[0] = grid[0][0];
        for (int c = 1; c < n; c++) {
            dp[c] = dp[c - 1] + grid[0][c];
        }

        for (int r = 1; r < m; r++) {
            dp[0] += grid[r][0];
            for (int c = 1; c < n; c++) {
                dp[c] = grid[r][c] + Math.min(dp[c], dp[c - 1]);
            }
        }

        return dp[n - 1];
    }

    public static void main(String[] args) {
        int[][] grid1 = {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
        };
        System.out.println("Min path sum 1: " + minPathSum(grid1) + " (Expected: 7)");

        int[][] grid2 = {
            {1, 2, 3},
            {4, 5, 6}
        };
        System.out.println("Min path sum 2: " + minPathSum(grid2) + " (Expected: 12)");
    }
}
