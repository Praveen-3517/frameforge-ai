import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

/**
 * Problem: Dijkstra's Shortest Path Algorithm
 * Asked in: Google, Amazon, Microsoft, Uber, Meta
 * 
 * Given a weighted, directed or undirected graph with non-negative edge weights
 * and a source vertex, find the shortest path distances from the source to all vertices.
 * 
 * Approach:
 * PriorityQueue (Min-Heap) Greedy Exploration:
 * 1. Initialize dist[] array with infinity; dist[source] = 0.
 * 2. Min-Heap stores pairs (vertex, currentDist), ordered by currentDist ascending.
 * 3. Extract node `u` with smallest distance:
 *    - If popped distance > dist[u], ignore (stale entry).
 *    - For each outgoing edge (u, v, weight):
 *      - If dist[u] + weight < dist[v]:
 *        - Update dist[v] = dist[u] + weight.
 *        - Push (v, dist[v]) to heap.
 * 
 * Time Complexity: O((V + E) log V) with binary heap.
 * Space Complexity: O(V + E) for adjacency list and distance array.
 */
class DijkstraShortestPathAlgorithm {

    static class Edge {
        int to;
        int weight;
        Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    public static int[] dijkstra(int n, List<List<Edge>> adj, int source) {
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;

        // Min-heap: [vertex, distance]
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{source, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int u = curr[0];
            int d = curr[1];

            if (d > dist[u]) continue; // Skip outdated distance

            for (Edge edge : adj.get(u)) {
                int v = edge.to;
                int weight = edge.weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.offer(new int[]{v, dist[v]});
                }
            }
        }

        return dist;
    }

    public static void main(String[] args) {
        int n = 5;
        List<List<Edge>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        adj.get(0).add(new Edge(1, 4));
        adj.get(0).add(new Edge(2, 1));
        adj.get(2).add(new Edge(1, 2));
        adj.get(1).add(new Edge(3, 1));
        adj.get(2).add(new Edge(3, 5));
        adj.get(3).add(new Edge(4, 3));

        int[] dist = dijkstra(n, adj, 0);
        System.out.println("Shortest distances from 0: " + Arrays.toString(dist));
        // Expected: [0, 3, 1, 4, 7]
    }
}
