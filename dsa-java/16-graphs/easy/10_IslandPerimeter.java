/**
 * Problem: Island Perimeter (LeetCode 463)
 * Asked in: Facebook, Google, Amazon, Apple
 * 
 * You are given row x col grid representing a map where grid[i][j] = 1 represents
 * land and grid[i][j] = 0 represents water. Grid cells are connected horizontally/vertically.
 * Determine the perimeter of the island.
 * 
 * Approach:
 * Counting edges:
 * - Each land cell initially contributes 4 edges.
 * - For each land cell, check its top and left neighbor.
 * - If top neighbor is land, both share an edge -> subtract 2.
 * - If left neighbor is land, both share an edge -> subtract 2.
 * 
 * Time Complexity: O(M * N) single pass.
 * Space Complexity: O(1) auxiliary space.
 */
class IslandPerimeter {

    public static int islandPerimeter(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int perimeter = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    perimeter += 4;

                    // Check upper neighbor
                    if (r > 0 && grid[r - 1][c] == 1) {
                        perimeter -= 2;
                    }
                    // Check left neighbor
                    if (c > 0 && grid[r][c - 1] == 1) {
                        perimeter -= 2;
                    }
                }
            }
        }

        return perimeter;
    }

    public static void main(String[] args) {
        int[][] grid = {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0}
        };

        System.out.println("Island Perimeter: " + islandPerimeter(grid) + " (Expected: 16)");
    }
}
