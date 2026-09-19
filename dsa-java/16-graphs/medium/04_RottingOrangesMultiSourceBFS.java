import java.util.ArrayDeque;
import java.util.Queue;

/**
 * Problem: Rotting Oranges (LeetCode 994)
 * Asked in: Amazon, Microsoft, Google, Bloomberg
 * 
 * You are given an m x n grid containing values:
 * - 0: Empty cell
 * - 1: Fresh orange
 * - 2: Rotten orange
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange.
 * If this is impossible, return -1.
 * 
 * Approach:
 * Multi-Source Breadth-First Search (BFS):
 * 1. Count fresh oranges.
 * 2. Enqueue all initial rotten oranges (cells with value 2) at time 0.
 * 3. Process BFS layer by layer (minute by minute):
 *    - Expand 4 directions; if fresh orange (1) found:
 *      - Turn it rotten (2), decrement freshCount, enqueue it.
 * 4. Return minutes if freshCount == 0, else -1.
 * 
 * Time Complexity: O(M * N) visiting each cell once.
 * Space Complexity: O(M * N) queue space.
 */
class RottingOrangesMultiSourceBFS {

    public static int orangesRotting(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int freshCount = 0;

        Queue<int[]> queue = new ArrayDeque<>();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 2) {
                    queue.offer(new int[]{r, c});
                } else if (grid[r][c] == 1) {
                    freshCount++;
                }
            }
        }

        if (freshCount == 0) return 0;

        int minutes = 0;
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!queue.isEmpty() && freshCount > 0) {
            int size = queue.size();
            minutes++;

            for (int i = 0; i < size; i++) {
                int[] curr = queue.poll();
                int r = curr[0];
                int c = curr[1];

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // rotten
                        freshCount--;
                        queue.offer(new int[]{nr, nc});
                    }
                }
            }
        }

        return freshCount == 0 ? minutes : -1;
    }

    public static void main(String[] args) {
        int[][] grid1 = {
            {2, 1, 1},
            {1, 1, 0},
            {0, 1, 1}
        };
        System.out.println("Minutes to rot 1: " + orangesRotting(grid1) + " (Expected: 4)");

        int[][] grid2 = {
            {2, 1, 1},
            {0, 1, 1},
            {1, 0, 1}
        };
        System.out.println("Minutes to rot 2: " + orangesRotting(grid2) + " (Expected: -1)");
    }
}
