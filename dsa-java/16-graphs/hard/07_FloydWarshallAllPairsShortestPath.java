import java.util.Arrays;

/**
 * Problem: Floyd-Warshall All-Pairs Shortest Path Algorithm
 * Asked in: Google, Amazon, Adobe, Oracle
 * 
 * Given an adjacency matrix graph with V vertices, find the shortest distances
 * between every pair of vertices.
 * 
 * Approach:
 * Dynamic Programming:
 * Let dist[i][j] be the shortest distance from vertex i to vertex j using intermediate
 * vertices from set {0, 1, ..., k}.
 * State Transition:
 * dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 * Negative Cycle Check:
 * If any dist[i][i] < 0 after completion, a negative weight cycle exists.
 * 
 * Time Complexity: O(V^3) with 3 nested loops.
 * Space Complexity: O(V^2) for distance matrix.
 */
class FloydWarshallAllPairsShortestPath {

    private static final int INF = 1_000_000_000;

    public static int[][] floydWarshall(int[][] graph) {
        int n = graph.length;
        int[][] dist = new int[n][n];

        for (int i = 0; i < n; i++) {
            dist[i] = Arrays.copyOf(graph[i], n);
        }

        // Try every vertex k as an intermediate step
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Check for negative cycle
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                System.out.println("Graph contains negative weight cycle!");
                return null;
            }
        }

        return dist;
    }

    public static void main(String[] args) {
        int[][] graph = {
            {0, 5, INF, 10},
            {INF, 0, 3, INF},
            {INF, INF, 0, 1},
            {INF, INF, INF, 0}
        };

        int[][] dist = floydWarshall(graph);
        System.out.println("All Pairs Shortest Paths:");
        for (int[] row : dist) {
            System.out.println(Arrays.toString(row));
        }
        // Expected:
        // [0, 5, 8, 9]
        // [INF, 0, 3, 4]
        // [INF, INF, 0, 1]
        // [INF, INF, INF, 0]
    }
}
