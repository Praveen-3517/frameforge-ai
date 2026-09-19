import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Graph Adjacency List Representation with BFS & DFS
 * Asked in: Amazon, Microsoft, Adobe
 * 
 * Implement an undirected graph using an Adjacency List, supporting:
 * - addEdge(u, v)
 * - bfs(startNode)
 * - dfs(startNode)
 * 
 * Time Complexity:
 * - Edge addition: O(1)
 * - BFS Traversal: O(V + E)
 * - DFS Traversal: O(V + E)
 * Space Complexity: O(V + E) for adjacency list and visited states.
 */
class GraphAdjacencyListRepresentation {

    private final int vertices;
    private final List<List<Integer>> adjList;

    public GraphAdjacencyListRepresentation(int vertices) {
        this.vertices = vertices;
        this.adjList = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    public void addEdge(int u, int v) {
        adjList.get(u).add(v);
        adjList.get(v).add(u);
    }

    public List<Integer> bfs(int start) {
        List<Integer> order = new ArrayList<>();
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new ArrayDeque<>();

        visited[start] = true;
        queue.offer(start);

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            order.add(curr);

            for (int neighbor : adjList.get(curr)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(neighbor);
                }
            }
        }
        return order;
    }

    public List<Integer> dfs(int start) {
        List<Integer> order = new ArrayList<>();
        boolean[] visited = new boolean[vertices];
        dfsHelper(start, visited, order);
        return order;
    }

    private void dfsHelper(int u, boolean[] visited, List<Integer> order) {
        visited[u] = true;
        order.add(u);

        for (int neighbor : adjList.get(u)) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, order);
            }
        }
    }

    public static void main(String[] args) {
        GraphAdjacencyListRepresentation graph = new GraphAdjacencyListRepresentation(5);
        graph.addEdge(0, 1);
        graph.addEdge(0, 4);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);

        System.out.println("BFS from 0: " + graph.bfs(0));
        System.out.println("DFS from 0: " + graph.dfs(0));
    }
}
