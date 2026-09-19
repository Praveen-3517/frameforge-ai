import java.util.Arrays;

/**
 * Problem: Bellman-Ford Algorithm with Negative Cycle Detection
 * Asked in: Google, Microsoft, Amazon, Morgan Stanley
 * 
 * Given a directed, weighted graph with V vertices and E edges, and a source vertex:
 * 1. Find the shortest distances from the source to all vertices.
 * 2. Detect if there is a negative-weight cycle reachable from the source.
 * 
 * Approach:
 * Dynamic Programming Edge Relaxation:
 * - Initialize dist[] array with infinity; dist[source] = 0.
 * - Relax all E edges V - 1 times:
 *     if dist[u] != inf && dist[u] + weight < dist[v]:
 *         dist[v] = dist[u] + weight
 * - 1 extra relaxation pass (the V-th pass):
 *     If any edge can still be relaxed, a NEGATIVE WEIGHT CYCLE exists!
 * 
 * Time Complexity: O(V * E)
 * Space Complexity: O(V)
 */
class BellmanFordNegativeCycleDetection {

    static class Edge {
        int u, v, weight;
        Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
    }

    public static int[] bellmanFord(int n, Edge[] edges, int source) {
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        // Relax edges n - 1 times
        for (int i = 1; i < n; i++) {
            for (Edge edge : edges) {
                if (dist[edge.u] != Integer.MAX_VALUE && dist[edge.u] + edge.weight < dist[edge.v]) {
                    dist[edge.v] = dist[edge.u] + edge.weight;
                }
            }
        }

        // Check for negative cycle
        for (Edge edge : edges) {
            if (dist[edge.u] != Integer.MAX_VALUE && dist[edge.u] + edge.weight < dist[edge.v]) {
                System.out.println("Negative weight cycle detected!");
                return null; // Indicates negative cycle exists
            }
        }

        return dist;
    }

    public static void main(String[] args) {
        int n = 5;
        Edge[] edgesNoCycle = {
            new Edge(0, 1, -1),
            new Edge(0, 2, 4),
            new Edge(1, 2, 3),
            new Edge(1, 3, 2),
            new Edge(1, 4, 2),
            new Edge(3, 2, 5),
            new Edge(3, 1, 1),
            new Edge(4, 3, -3)
        };

        int[] dist = bellmanFord(n, edgesNoCycle, 0);
        System.out.println("Shortest distances: " + Arrays.toString(dist));
        // Expected: [0, -1, 2, -2, 1]

        Edge[] edgesWithCycle = {
            new Edge(0, 1, 1),
            new Edge(1, 2, -1),
            new Edge(2, 3, -1),
            new Edge(3, 1, -1) // Cycle: 1 -> 2 -> 3 -> 1 with sum -3
        };

        int[] distCycle = bellmanFord(4, edgesWithCycle, 0);
        System.out.println("Cycle test result: " + (distCycle == null ? "Cycle Detected" : "No cycle"));
    }
}
