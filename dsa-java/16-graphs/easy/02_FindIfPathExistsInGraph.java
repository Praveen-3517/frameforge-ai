import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Find if Path Exists in Graph (LeetCode 1971)
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * There is a bi-directional graph with n vertices, where each vertex is labeled
 * from 0 to n - 1. Given 2D array edges, source and destination, determine if there
 * is a valid path that exists from source to destination.
 * 
 * Approach:
 * Breadth-First Search (BFS):
 * 1. Build adjacency list from edges.
 * 2. Start BFS queue from source, mark source visited.
 * 3. If destination is dequeued, return true immediately.
 * 4. If queue empties without reaching destination, return false.
 * 
 * Time Complexity: O(V + E) where V = n and E = edges.length.
 * Space Complexity: O(V + E) for adjacency list and BFS queue.
 */
class FindIfPathExistsInGraph {

    public static boolean validPath(int n, int[][] edges, int source, int destination) {
        if (source == destination) return true;

        List<List<Integer>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new ArrayDeque<>();

        visited[source] = true;
        queue.offer(source);

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            if (curr == destination) return true;

            for (int neighbor : adj.get(curr)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(neighbor);
                }
            }
        }

        return false;
    }

    public static void main(String[] args) {
        int n1 = 3;
        int[][] edges1 = {{0, 1}, {1, 2}, {2, 0}};
        System.out.println("Path 0->2 exists: " + validPath(n1, edges1, 0, 2) + " (Expected: true)");

        int n2 = 6;
        int[][] edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
        System.out.println("Path 0->5 exists: " + validPath(n2, edges2, 0, 5) + " (Expected: false)");
    }
}
