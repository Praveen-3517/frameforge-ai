import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

/**
 * Problem: Prim's Minimum Spanning Tree (MST) Algorithm
 * Asked in: Amazon, Google, Microsoft, Adobe
 * 
 * Given an undirected, weighted, connected graph with V vertices, find the minimum
 * spanning tree weight using Prim's Algorithm.
 * 
 * Approach:
 * Greedy Min-Heap Growing Strategy:
 * 1. Start with an arbitrary vertex (e.g. 0) in the MST.
 * 2. Maintain a PriorityQueue storing [vertex, edgeWeight, parent].
 * 3. In each step, extract the lowest-cost edge leading to an unvisited node.
 * 4. Add the node to the visited set, accumulate edge weight, and push all its incident edges
 *    connecting to unvisited nodes into the Min-Heap.
 * 
 * Time Complexity: O((V + E) log V) with Min-Heap.
 * Space Complexity: O(V + E) for adjacency list and heap.
 */
class PrimMinimumSpanningTree {

    static class Edge {
        int to, weight;
        Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    public static int primMST(int n, List<List<Edge>> adj) {
        boolean[] inMST = new boolean[n];
        // Min-heap storing: [node, weight]
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));

        pq.offer(new int[]{0, 0});
        int totalWeight = 0;
        int nodesIncluded = 0;

        while (!pq.isEmpty() && nodesIncluded < n) {
            int[] curr = pq.poll();
            int u = curr[0];
            int weight = curr[1];

            if (inMST[u]) continue;

            inMST[u] = true;
            totalWeight += weight;
            nodesIncluded++;

            for (Edge edge : adj.get(u)) {
                if (!inMST[edge.to]) {
                    pq.offer(new int[]{edge.to, edge.weight});
                }
            }
        }

        return totalWeight;
    }

    public static void main(String[] args) {
        int n = 4;
        List<List<Edge>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        adj.get(0).add(new Edge(1, 10));
        adj.get(1).add(new Edge(0, 10));

        adj.get(0).add(new Edge(2, 6));
        adj.get(2).add(new Edge(0, 6));

        adj.get(0).add(new Edge(3, 5));
        adj.get(3).add(new Edge(0, 5));

        adj.get(1).add(new Edge(3, 15));
        adj.get(3).add(new Edge(1, 15));

        adj.get(2).add(new Edge(3, 4));
        adj.get(3).add(new Edge(2, 4));

        int weight = primMST(n, adj);
        System.out.println("Prim's MST Total Weight: " + weight + " (Expected: 19)");
    }
}
