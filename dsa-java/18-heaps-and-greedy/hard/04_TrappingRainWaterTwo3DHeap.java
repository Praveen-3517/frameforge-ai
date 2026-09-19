import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Problem: Trapping Rain Water II (LeetCode 407)
 * Asked in: Google, Amazon, Twitter
 * 
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map,
 * return the volume of water it can trap after raining.
 * 
 * Approach:
 * PriorityQueue / Min-Heap Boundary Inward Shrinking:
 * - The water level is determined by the LOWEST boundary wall currently surrounding the inner cells.
 * 1. Push all outer boundary cells into a Min-Heap and mark them visited.
 * 2. While heap is not empty:
 *    - Poll the lowest boundary cell [r, c, h].
 *    - Check all 4 unvisited neighbors [nr, nc]:
 *      - If neighbor's height < h: trappedWater += (h - neighborHeight).
 *      - Offer neighbor into heap with effective boundary height = max(h, neighborHeight).
 *      - Mark neighbor visited.
 * 
 * Time Complexity: O(M * N log(M * N))
 * Space Complexity: O(M * N)
 */
class TrappingRainWaterTwo3DHeap {

    public static int trapRainWater(int[][] heightMap) {
        if (heightMap == null || heightMap.length <= 2 || heightMap[0].length <= 2) {
            return 0;
        }

        int rows = heightMap.length;
        int cols = heightMap[0].length;
        boolean[][] visited = new boolean[rows][cols];

        // Min-heap: [row, col, height]
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[2]));

        // Add first and last columns to heap
        for (int r = 0; r < rows; r++) {
            minHeap.offer(new int[]{r, 0, heightMap[r][0]});
            minHeap.offer(new int[]{r, cols - 1, heightMap[r][cols - 1]});
            visited[r][0] = true;
            visited[r][cols - 1] = true;
        }

        // Add first and last rows to heap
        for (int c = 1; c < cols - 1; c++) {
            minHeap.offer(new int[]{0, c, heightMap[0][c]});
            minHeap.offer(new int[]{rows - 1, c, heightMap[rows - 1][c]});
            visited[0][c] = true;
            visited[rows - 1][c] = true;
        }

        int totalWater = 0;
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!minHeap.isEmpty()) {
            int[] cell = minHeap.poll();
            int r = cell[0];
            int c = cell[1];
            int h = cell[2];

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    totalWater += Math.max(0, h - heightMap[nr][nc]);
                    minHeap.offer(new int[]{nr, nc, Math.max(h, heightMap[nr][nc])});
                }
            }
        }

        return totalWater;
    }

    public static void main(String[] args) {
        int[][] heightMap = {
            {1, 4, 3, 1, 3, 2},
            {3, 2, 1, 3, 2, 4},
            {2, 3, 3, 2, 3, 1}
        };

        System.out.println("Trapped 3D water: " + trapRainWater(heightMap) + " (Expected: 4)");
    }
}
