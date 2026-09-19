import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Problem: Kruskal's Minimum Spanning Tree (MST) Algorithm
 * Asked in: Google, Microsoft, Amazon, Cisco
 * 
 * Given an undirected, connected, weighted graph, find a subset of edges that connects
 * all vertices together without cycles and with the minimum possible total edge weight.
 * 
 * Approach:
 * Greedy Strategy with Disjoint Set Union (DSU):
 * 1. Sort all edges in non-decreasing order of their weights.
 * 2. Initialize a DSU for all V vertices.
 * 3. Iterate through sorted edges:
 *    - If find(u) != find(v), edge does not create a cycle:
 *      - Add to MST.
 *      - union(u, v).
 *      - Stop when MST contains V - 1 edges.
 * 
 * Time Complexity: O(E log E) for sorting edges.
 * Space Complexity: O(V) for DSU.
 */
class KruskalMinimumSpanningTree {

    static class Edge {
        int u, v, weight;
        Edge(int u, int v, int weight) {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }

        @Override
        public String toString() {
            return "(" + u + " - " + v + " : " + weight + ")";
        }
    }

    static class DSU {
        int[] parent;
        int[] rank;

        DSU(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }

        boolean union(int x, int y) {
            int rx = find(x);
            int ry = find(y);
            if (rx == ry) return false;

            if (rank[rx] < rank[ry]) {
                parent[rx] = ry;
            } else if (rank[rx] > rank[ry]) {
                parent[ry] = rx;
            } else {
                parent[ry] = rx;
                rank[rx]++;
            }
            return true;
        }
    }

    public static int kruskalMST(int n, List<Edge> edges, List<Edge> mstEdges) {
        Collections.sort(edges, Comparator.comparingInt(e -> e.weight));
        DSU dsu = new DSU(n);
        int totalWeight = 0;

        for (Edge edge : edges) {
            if (dsu.union(edge.u, edge.v)) {
                totalWeight += edge.weight;
                mstEdges.add(edge);
                if (mstEdges.size() == n - 1) break;
            }
        }

        return totalWeight;
    }

    public static void main(String[] args) {
        int n = 4;
        List<Edge> edges = Arrays.asList(
            new Edge(0, 1, 10),
            new Edge(0, 2, 6),
            new Edge(0, 3, 5),
            new Edge(1, 3, 15),
            new Edge(2, 3, 4)
        );

        List<Edge> mst = new ArrayList<>();
        int weight = kruskalMST(n, edges, mst);

        System.out.println("MST Total Weight: " + weight + " (Expected: 19)");
        System.out.println("MST Edges: " + mst);
    }
}
