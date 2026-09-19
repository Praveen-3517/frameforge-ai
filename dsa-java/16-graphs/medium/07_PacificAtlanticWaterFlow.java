import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Problem: Pacific Atlantic Water Flow (LeetCode 417)
 * Asked in: Google, Amazon, Facebook, Microsoft
 * 
 * Given an m x n matrix of non-negative integers representing the height of each unit cell.
 * Water can flow to neighboring cells directly north, south, east, and west if the neighboring
 * cell's height is less than or equal to the current cell's height.
 * The Pacific ocean touches the island's top and left edges, and the Atlantic ocean touches
 * the bottom and right edges.
 * Return a list of grid coordinates where water can flow to both oceans.
 * 
 * Approach:
 * Reverse Flow DFS:
 * Instead of simulating water flowing downhill into oceans, simulate water flowing
 * UPHILL from ocean boundaries inward (where neighbor height >= current height).
 * 1. Create two boolean matrices: pacificReachable and atlanticReachable.
 * 2. Run DFS from all Pacific border cells into island.
 * 3. Run DFS from all Atlantic border cells into island.
 * 4. Cells where both are true are the valid answers!
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
class PacificAtlanticWaterFlow {

    public static List<List<Integer>> pacificAtlantic(int[][] heights) {
        List<List<Integer>> result = new ArrayList<>();
        if (heights == null || heights.length == 0) return result;

        int rows = heights.length;
        int cols = heights[0].length;

        boolean[][] pacific = new boolean[rows][cols];
        boolean[][] atlantic = new boolean[rows][cols];

        // DFS from left and right edges
        for (int r = 0; r < rows; r++) {
            dfs(heights, r, 0, pacific, heights[r][0]);
            dfs(heights, r, cols - 1, atlantic, heights[r][cols - 1]);
        }

        // DFS from top and bottom edges
        for (int c = 0; c < cols; c++) {
            dfs(heights, 0, c, pacific, heights[0][c]);
            dfs(heights, rows - 1, c, atlantic, heights[rows - 1][c]);
        }

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.add(Arrays.asList(r, c));
                }
            }
        }

        return result;
    }

    private static void dfs(int[][] heights, int r, int c, boolean[][] ocean, int prevHeight) {
        if (r < 0 || r >= heights.length || c < 0 || c >= heights[0].length) return;
        if (ocean[r][c] || heights[r][c] < prevHeight) return;

        ocean[r][c] = true;

        dfs(heights, r + 1, c, ocean, heights[r][c]);
        dfs(heights, r - 1, c, ocean, heights[r][c]);
        dfs(heights, r, c + 1, ocean, heights[r][c]);
        dfs(heights, r, c - 1, ocean, heights[r][c]);
    }

    public static void main(String[] args) {
        int[][] heights = {
            {1, 2, 2, 3, 5},
            {3, 2, 3, 4, 4},
            {2, 4, 5, 3, 1},
            {6, 7, 1, 4, 5},
            {5, 1, 1, 2, 4}
        };

        List<List<Integer>> res = pacificAtlantic(heights);
        System.out.println("Cells flowing to both: " + res);
        // Expected: [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
    }
}
