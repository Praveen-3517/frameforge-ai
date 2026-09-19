import java.util.Arrays;

/**
 * Problem: Redundant Connection (LeetCode 684)
 * Asked in: Google, Amazon, Facebook
 * 
 * A tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n,
 * with one additional edge added.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
 * 
 * Approach:
 * Disjoint Set Union (DSU):
 * - Initialize DSU with n + 1 elements.
 * - Iterate through each edge [u, v]:
 *   - If find(u) == find(v), u and v are ALREADY connected! Adding this edge creates a cycle.
 *     Thus, [u, v] is the redundant edge.
 *   - Otherwise, union(u, v).
 * 
 * Time Complexity: O(N * alpha(N))
 * Space Complexity: O(N) for DSU parent array.
 */
class RedundantConnectionUnionFind {

    public static int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        int[] parent = new int[n + 1];
        for (int i = 1; i <= n; i++) parent[i] = i;

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];

            int rootU = find(parent, u);
            int rootV = find(parent, v);

            if (rootU == rootV) {
                return edge; // Found the cycle-forming edge
            }
            parent[rootU] = rootV;
        }

        return new int[0];
    }

    private static int find(int[] parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }

    public static void main(String[] args) {
        int[][] edges1 = {{1, 2}, {1, 3}, {2, 3}};
        System.out.println("Redundant edge: " + Arrays.toString(findRedundantConnection(edges1)) + " (Expected: [2, 3])");

        int[][] edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
        System.out.println("Redundant edge: " + Arrays.toString(findRedundantConnection(edges2)) + " (Expected: [1, 4])");
    }
}
