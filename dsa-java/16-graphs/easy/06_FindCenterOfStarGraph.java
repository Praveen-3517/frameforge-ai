/**
 * Problem: Find Center of Star Graph (LeetCode 1791)
 * Asked in: Amazon, Microsoft
 * 
 * There is an undirected star graph consisting of n nodes labeled from 1 to n.
 * A star graph is a graph where there is one center node and exactly n - 1 edges
 * that connect the center node with every other node.
 * Given a 2D integer array edges where each edges[i] = [ui, vi], return the center.
 * 
 * Approach:
 * Since the center node is connected to every other node, it MUST be present in EVERY edge.
 * Thus, we only need to compare the first two edges: edges[0] and edges[1].
 * Whichever vertex is shared between these two edges is guaranteed to be the center!
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class FindCenterOfStarGraph {

    public static int findCenter(int[][] edges) {
        // If edges[0][0] is present in edges[1], it's the center; otherwise edges[0][1] is.
        if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) {
            return edges[0][0];
        }
        return edges[0][1];
    }

    public static void main(String[] args) {
        int[][] edges1 = {{1, 2}, {2, 3}, {4, 2}};
        System.out.println("Center: " + findCenter(edges1) + " (Expected: 2)");

        int[][] edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};
        System.out.println("Center: " + findCenter(edges2) + " (Expected: 1)");
    }
}
