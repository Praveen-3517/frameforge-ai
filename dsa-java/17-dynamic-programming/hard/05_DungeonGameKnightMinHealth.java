import java.util.Arrays;

/**
 * Problem: Dungeon Game (LeetCode 174)
 * Asked in: Google, Amazon, Microsoft
 * 
 * The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon.
 * The dungeon consists of m x n rooms laid out in a 2D grid. The knight starts at top-left (0, 0).
 * At each room, the knight's health points change by dungeon[i][j]. If at any point health <= 0, he dies.
 * Knight can only move right or down.
 * Return the knight's minimum initial health so that he can rescue the princess.
 * 
 * Approach:
 * Reverse Dynamic Programming (Bottom-Right to Top-Left):
 * Let dp[i][j] be the minimum health the knight needs BEFORE stepping into room (i, j).
 * - Base at destination (m - 1, n - 1):
 *   dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]).
 * - General transition:
 *   minHealthToExit = min(dp[i + 1][j], dp[i][j + 1])
 *   dp[i][j] = max(1, minHealthToExit - dungeon[i][j])
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) (or O(N) space optimized).
 */
class DungeonGameKnightMinHealth {

    public static int calculateMinimumHP(int[][] dungeon) {
        int m = dungeon.length;
        int n = dungeon[0].length;
        int[][] dp = new int[m + 1][n + 1];

        // Fill extra row and col with infinity
        for (int i = 0; i <= m; i++) Arrays.fill(dp[i], Integer.MAX_VALUE);

        // Base cases for bottom-right destination
        dp[m][n - 1] = 1;
        dp[m - 1][n] = 1;

        for (int r = m - 1; r >= 0; r--) {
            for (int c = n - 1; c >= 0; c--) {
                int minExit = Math.min(dp[r + 1][c], dp[r][c + 1]);
                dp[r][c] = Math.max(1, minExit - dungeon[r][c]);
            }
        }

        return dp[0][0];
    }

    public static void main(String[] args) {
        int[][] dungeon = {
            {-2, -3, 3},
            {-5, -10, 1},
            {10, 30, -5}
        };

        System.out.println("Min initial health: " + calculateMinimumHP(dungeon) + " (Expected: 7)");
    }
}
