import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Problem: Strongly Connected Components (Kosaraju's Algorithm)
 * Asked in: Google, Microsoft, Amazon, Directi
 * 
 * Given a directed graph with V vertices and E edges, find all Strongly Connected
 * Components (SCCs). An SCC is a maximal subgraph where every vertex is reachable
 * from every other vertex in that subgraph.
 * 
 * Approach:
 * Kosaraju's 2-Pass DFS Algorithm:
 * 1. Pass 1: Perform standard DFS on the original graph. When a vertex finishes
 *    exploring all its descendants, push it onto a stack (finish-time ordering).
 * 2. Transpose the graph: Reverse the direction of all directed edges.
 * 3. Pass 2: Pop vertices from the stack one by one. If a vertex is not yet visited
 *    in the transposed graph, launch DFS from it. All vertices reached in this DFS
 *    form one Strongly Connected Component!
 * 
 * Time Complexity: O(V + E) for two DFS passes and transpose.
 * Space Complexity: O(V + E) for reversed graph and stack.
 */
class StronglyConnectedComponentsKosaraju {

    public static List<List<Integer>> kosarajuSCC(int n, List<List<Integer>> adj) {
        // Step 1: DFS to get finish time ordering
        boolean[] visited = new boolean[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                fillOrder(i, adj, visited, stack);
            }
        }

        // Step 2: Reverse graph
        List<List<Integer>> transpose = new ArrayList<>(n);
        for (int i = 0; i < n; i++) transpose.add(new ArrayList<>());

        for (int u = 0; u < n; u++) {
            for (int v : adj.get(u)) {
                transpose.get(v).add(u);
            }
        }

        // Step 3: DFS on transposed graph in order of stack
        java.util.Arrays.fill(visited, false);
        List<List<Integer>> sccs = new ArrayList<>();

        while (!stack.isEmpty()) {
            int u = stack.pop();
            if (!visited[u]) {
                List<Integer> component = new ArrayList<>();
                dfsCollect(u, transpose, visited, component);
                sccs.add(component);
            }
        }

        return sccs;
    }

    private static void fillOrder(int u, List<List<Integer>> adj, boolean[] visited, Deque<Integer> stack) {
        visited[u] = true;
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                fillOrder(v, adj, visited, stack);
            }
        }
        stack.push(u);
    }

    private static void dfsCollect(int u, List<List<Integer>> transpose, boolean[] visited, List<Integer> component) {
        visited[u] = true;
        component.add(u);
        for (int v : transpose.get(u)) {
            if (!visited[v]) {
                dfsCollect(v, transpose, visited, component);
            }
        }
    }

    public static void main(String[] args) {
        int n = 5;
        List<List<Integer>> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        // Graph: 1 -> 0, 0 -> 2, 2 -> 1, 0 -> 3, 3 -> 4
        adj.get(1).add(0);
        adj.get(0).add(2);
        adj.get(2).add(1);
        adj.get(0).add(3);
        adj.get(3).add(4);

        List<List<Integer>> sccs = kosarajuSCC(n, adj);
        System.out.println("Strongly Connected Components: " + sccs);
        // Expected SCCs: [0, 1, 2], [3], [4]
    }
}
