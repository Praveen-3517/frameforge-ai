/**
 * Problem: Max Area of Island (LeetCode 695)
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally. The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 * 
 * Approach:
 * Depth-First Search (DFS):
 * For every cell (r, c) == 1:
 * - Sink cell (set grid[r][c] = 0).
 * - Return 1 + dfs(up) + dfs(down) + dfs(left) + dfs(right).
 * - Maintain maximum area across all components.
 * 
 * Time Complexity: O(M * N) where M is rows, N is columns.
 * Space Complexity: O(M * N) worst case recursion stack.
 */
class MaxAreaOfIslandDFS {

    public static int maxAreaOfIsland(int[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int maxArea = 0;
        int rows = grid.length;
        int cols = grid[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    int area = dfs(grid, r, c);
                    maxArea = Math.max(maxArea, area);
                }
            }
        }

        return maxArea;
    }

    private static int dfs(int[][] grid, int r, int c) {
        if (r < 0 || r >= grid.length || c < 0 || c >= grid[0].length || grid[r][c] != 1) {
            return 0;
        }

        grid[r][c] = 0; // mark visited

        return 1 
            + dfs(grid, r + 1, c) 
            + dfs(grid, r - 1, c) 
            + dfs(grid, r, c + 1) 
            + dfs(grid, r, c - 1);
    }

    public static void main(String[] args) {
        int[][] grid = {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
        };

        System.out.println("Max Area: " + maxAreaOfIsland(grid) + " (Expected: 6)");
    }
}
