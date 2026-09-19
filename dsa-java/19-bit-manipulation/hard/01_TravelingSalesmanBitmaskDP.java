import java.util.Arrays;

/**
 * Problem: Traveling Salesman Problem (TSP) using Bitmask DP (LeetCode-style classic)
 * Asked in: Google, Amazon, Microsoft
 * 
 * Given n cities and a distance matrix dist[][], find the shortest route that:
 * - Visits every city exactly once.
 * - Returns to the starting city.
 * 
 * Approach - Bitmask DP (Held-Karp Algorithm):
 * dp[mask][i] = minimum cost to visit exactly the cities indicated by bitmask `mask`,
 *               ending at city i.
 * 
 * Transition:
 * For each city j NOT in mask:
 *   dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[i][j])
 * 
 * Base case: dp[1][0] = 0 (starting at city 0 with city 0 visited).
 * Answer: min over all i of (dp[(1<<n)-1][i] + dist[i][0]).
 * 
 * Time Complexity: O(2^N * N^2)
 * Space Complexity: O(2^N * N)
 */
class TravelingSalesmanBitmaskDP {

    public static int tsp(int[][] dist) {
        int n = dist.length;
        int FULL_MASK = (1 << n) - 1;
        int[][] dp = new int[1 << n][n];

        for (int[] row : dp) Arrays.fill(row, Integer.MAX_VALUE / 2);
        dp[1][0] = 0; // Start at city 0

        for (int mask = 1; mask <= FULL_MASK; mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue; // i not in mask
                if (dp[mask][i] == Integer.MAX_VALUE / 2) continue;

                // Try going to each unvisited city j
                for (int j = 0; j < n; j++) {
                    if ((mask & (1 << j)) != 0) continue; // j already visited
                    int newMask = mask | (1 << j);
                    dp[newMask][j] = Math.min(dp[newMask][j], dp[mask][i] + dist[i][j]);
                }
            }
        }

        int minTour = Integer.MAX_VALUE;
        for (int i = 1; i < n; i++) {
            if (dp[FULL_MASK][i] != Integer.MAX_VALUE / 2) {
                minTour = Math.min(minTour, dp[FULL_MASK][i] + dist[i][0]);
            }
        }

        return minTour;
    }

    public static void main(String[] args) {
        int[][] dist = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
        };

        System.out.println("Minimum TSP Tour: " + tsp(dist) + " (Expected: 80)");
        // 0 -> 1 -> 3 -> 2 -> 0 = 10 + 25 + 30 + 15 = 80
    }
}
