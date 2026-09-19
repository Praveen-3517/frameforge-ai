import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Problem: Critical Connections in a Network / Bridges (LeetCode 1192)
 * Asked in: Amazon, Google, Facebook
 * 
 * There are n servers numbered 0 to n - 1 connected by undirected server-to-server connections.
 * A critical connection is a connection that, if removed, will make some servers unable
 * to reach other servers (a bridge). Return all critical connections in the network.
 * 
 * Approach:
 * Tarjan's Bridge-Finding Algorithm (DFS):
 * Maintain two arrays:
 * - tin[u]: discovery timestamp of node u.
 * - low[u]: lowest discovery timestamp reachable from u using backward edges.
 * For each neighbor v of u (excluding parent):
 * - If v is unvisited:
 *   - Recurse dfs(v, u).
 *   - low[u] = min(low[u], low[v]).
 *   - If low[v] > tin[u], then edge (u, v) is a CRITICAL BRIDGE! (v cannot reach u or ancestors of u without this edge).
 * - Else (back-edge to already visited node):
 *   - low[u] = min(low[u], tin[v]).
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */
class CriticalConnectionsBridgesTarjan {

    private static int timer;

    public static List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        List<List<Integer>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        for (List<Integer> edge : connections) {
            int u = edge.get(0);
            int v = edge.get(1);
            adj.get(u).add(v);
            adj.get(v).add(u);
        }

        int[] tin = new int[n];
        int[] low = new int[n];
        boolean[] visited = new boolean[n];
        List<List<Integer>> bridges = new ArrayList<>();
        timer = 0;

        dfs(0, -1, adj, tin, low, visited, bridges);

        return bridges;
    }

    private static void dfs(int u, int parent, List<List<Integer>> adj, int[] tin, int[] low, boolean[] visited, List<List<Integer>> bridges) {
        visited[u] = true;
        tin[u] = low[u] = ++timer;

        for (int v : adj.get(u)) {
            if (v == parent) continue;

            if (visited[v]) {
                low[u] = Math.min(low[u], tin[v]);
            } else {
                dfs(v, u, adj, tin, low, visited, bridges);
                low[u] = Math.min(low[u], low[v]);

                if (low[v] > tin[u]) {
                    bridges.add(Arrays.asList(u, v));
                }
            }
        }
    }

    public static void main(String[] args) {
        List<List<Integer>> connections = new ArrayList<>();
        connections.add(Arrays.asList(0, 1));
        connections.add(Arrays.asList(1, 2));
        connections.add(Arrays.asList(2, 0));
        connections.add(Arrays.asList(1, 3));

        List<List<Integer>> bridges = criticalConnections(4, connections);
        System.out.println("Bridges: " + bridges + " (Expected: [[1, 3]])");
    }
}
