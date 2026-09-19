/*
 * Problem Statement:
 * Given an undirected graph represented by an adjacency matrix and an integer m,
 * determine if the graph can be colored with at most m colors such that no two adjacent
 * vertices of the graph are colored with the same color.
 * (The M-Coloring Decision Problem)
 * 
 * Example:
 * Graph with 4 vertices forming a square with one diagonal:
 * (0)-(1)
 *  | \ |
 * (2)-(3)
 * m = 3 colors -> Possible (returns true).
 * 
 * Asked in: Google, Microsoft, Amazon
 */

import java.util.Arrays;

class MColoringGraphBacktracking {

    public static boolean graphColoring(int[][] graph, int m, int n) {
        int[] color = new int[n]; // 0 means uncolored
        return solve(0, graph, m, n, color);
    }

    private static boolean solve(int vertex, int[][] graph, int m, int n, int[] color) {
        if (vertex == n) return true; // All vertices colored successfully!

        for (int c = 1; c <= m; c++) {
            if (isSafe(vertex, graph, color, c, n)) {
                color[vertex] = c;
                if (solve(vertex + 1, graph, m, n, color)) {
                    return true;
                }
                color[vertex] = 0; // backtrack
            }
        }

        return false;
    }

    private static boolean isSafe(int v, int[][] graph, int[] color, int c, int n) {
        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[v][neighbor] == 1 && color[neighbor] == c) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        int n = 4;
        int[][] graph = {
            {0, 1, 1, 1},
            {1, 0, 1, 0},
            {1, 1, 0, 1},
            {1, 0, 1, 0}
        };

        int m1 = 3;
        System.out.println("Can color with " + m1 + " colors? " + graphColoring(graph, m1, n));

        int m2 = 2;
        System.out.println("Can color with " + m2 + " colors? " + graphColoring(graph, m2, n));
    }
}

/*
 * Time Complexity: O(m^V) where V is number of vertices and m is color count.
 * Space Complexity: O(V) for color assignment array and call stack.
 */
