import java.util.ArrayDeque;
import java.util.Queue;

/**
 * Problem: Number of Islands (LeetCode 200)
 * Asked in: Amazon, Google, Microsoft, Bloomberg, Meta
 * 
 * Given an m x n 2D binary grid grid which represents a map of '1's (land)
 * and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically.
 * 
 * Approach:
 * Breadth-First Search (BFS):
 * 1. Iterate through each cell (r, c).
 * 2. When '1' is found, increment islandCount, and launch BFS to mark all connected '1's as '0'.
 * 3. BFS uses a queue of encoded coordinates (r * cols + c) to save space.
 * 
 * Time Complexity: O(M * N) since each cell is visited and enqueued at most once.
 * Space Complexity: O(min(M, N)) for BFS queue size.
 */
class NumberOfIslandsBFS {

    public static int numIslands(char[][] grid) {
        if (grid == null || grid.length == 0) return 0;

        int rows = grid.length;
        int cols = grid[0].length;
        int islandCount = 0;

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    islandCount++;
                    // BFS to sink current island
                    Queue<Integer> queue = new ArrayDeque<>();
                    queue.offer(r * cols + c);
                    grid[r][c] = '0'; // mark visited

                    while (!queue.isEmpty()) {
                        int pos = queue.poll();
                        int currR = pos / cols;
                        int currC = pos % cols;

                        for (int d = 0; d < 4; d++) {
                            int nr = currR + dr[d];
                            int nc = currC + dc[d];

                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                                grid[nr][nc] = '0';
                                queue.offer(nr * cols + nc);
                            }
                        }
                    }
                }
            }
        }

        return islandCount;
    }

    public static void main(String[] args) {
        char[][] grid1 = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        };
        System.out.println("Islands in grid 1: " + numIslands(grid1) + " (Expected: 1)");

        char[][] grid2 = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        };
        System.out.println("Islands in grid 2: " + numIslands(grid2) + " (Expected: 3)");
    }
}
