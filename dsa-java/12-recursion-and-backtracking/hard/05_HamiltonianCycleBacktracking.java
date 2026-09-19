/*
 * Problem Statement:
 * A Hamiltonian cycle in an undirected graph is a closed path that visits every vertex
 * exactly once and returns to the starting vertex.
 * Given an adjacency matrix, find a Hamiltonian cycle if one exists.
 * (Classic NP-Complete Graph Problem)
 * 
 * Asked in: Google, Amazon, Cisco
 */

import java.util.Arrays;

class HamiltonianCycleBacktracking {

    public static boolean findHamiltonianCycle(int[][] graph, int n) {
        int[] path = new int[n];
        Arrays.fill(path, -1);

        // Put vertex 0 as first vertex in cycle
        path[0] = 0;

        if (!solve(1, graph, path, n)) {
            System.out.println("No Hamiltonian Cycle exists for this graph.");
            return false;
        }

        System.out.print("Hamiltonian Cycle found: ");
        for (int v : path) System.out.print(v + " -> ");
        System.out.println(path[0]);
        return true;
    }

    private static boolean solve(int pos, int[][] graph, int[] path, int n) {
        if (pos == n) {
            // Check if there is an edge from the last vertex to the first vertex (0)
            return graph[path[pos - 1]][path[0]] == 1;
        }

        for (int v = 1; v < n; v++) {
            if (isSafe(v, graph, path, pos)) {
                path[pos] = v;
                if (solve(pos + 1, graph, path, n)) return true;
                path[pos] = -1; // backtrack
            }
        }

        return false;
    }

    private static boolean isSafe(int v, int[][] graph, int[] path, int pos) {
        // Must have an edge from previous vertex
        if (graph[path[pos - 1]][v] == 0) return false;

        // Must not be already visited
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) return false;
        }

        return true;
    }

    public static void main(String[] args) {
        int n = 5;
        int[][] graph1 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0}
        };

        System.out.println("--- Hamiltonian Cycle Solver ---");
        findHamiltonianCycle(graph1, n);
    }
}

/*
 * Time Complexity: O(N!) in worst case.
 * Space Complexity: O(N) path array and call stack.
 */
