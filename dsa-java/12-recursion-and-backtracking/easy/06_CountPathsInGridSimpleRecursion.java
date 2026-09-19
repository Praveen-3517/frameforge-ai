/*
 * Problem Statement:
 * Given a grid of size m x n, count the number of unique paths from the top-left corner
 * (0, 0) to the bottom-right corner (m - 1, n - 1).
 * You are only allowed to move either down or right at any point in time.
 * (LeetCode 62: Unique Paths - Recursive & Memoized formulation)
 * 
 * Example:
 * Input: m = 3, n = 2
 * Output: 3
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 */

class CountPathsInGridSimpleRecursion {

    public static int uniquePaths(int m, int n) {
        int[][] memo = new int[m][n];
        return countPaths(0, 0, m, n, memo);
    }

    private static int countPaths(int r, int c, int m, int n, int[][] memo) {
        // Reached destination
        if (r == m - 1 && c == n - 1) return 1;

        // Out of bounds
        if (r >= m || c >= n) return 0;

        if (memo[r][c] != 0) return memo[r][c];

        // Move Right + Move Down
        return memo[r][c] = countPaths(r, c + 1, m, n, memo) + countPaths(r + 1, c, m, n, memo);
    }

    public static void main(String[] args) {
        int[][] testCases = {
            {3, 2},
            {3, 7},
            {7, 3},
            {3, 3}
        };

        System.out.println("--- Unique Grid Paths (Recursion + Memoization) ---");
        for (int[] t : testCases) {
            int m = t[0], n = t[1];
            System.out.printf("Grid %d x %d -> Unique Paths: %d%n", m, n, uniquePaths(m, n));
        }
    }
}

/*
 * Time Complexity: O(M * N) with memoization.
 * Space Complexity: O(M * N) memo table + O(M + N) stack depth.
 */
