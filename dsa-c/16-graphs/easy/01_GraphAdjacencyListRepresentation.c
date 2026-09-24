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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

static const int vertices;
    static const int*> adjList;

    GraphAdjacencyListRepresentation(int vertices) {
        this.vertices = vertices;
        this.adjList = new ArrayList<>(vertices);
        for (int i = 0; i < vertices; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    void addEdge(int u, int v) {
        adjList.get(u).add(v);
        adjList.get(v).add(u);
    }

    int* bfs(int start) {
        int* order = new ArrayList<>();
        bool[] visited = (bool*)malloc((vertices) * sizeof(bool));
        Queue<int> queue = new ArrayDeque<>();

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

    int* dfs(int start) {
        int* order = new ArrayList<>();
        bool[] visited = (bool*)malloc((vertices) * sizeof(bool));
        dfsHelper(start, visited, order);
        return order;
    }

    static void dfsHelper(int u, bool[] visited, int* order) {
        visited[u] = true;
        order.add(u);

        for (int neighbor : adjList.get(u)) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, order);
            }
        }
    }

    int main(void) {
        GraphAdjacencyListRepresentation graph = new GraphAdjacencyListRepresentation(5);
        graph.addEdge(0, 1);
        graph.addEdge(0, 4);
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);

        printf("BFS from 0: %d\n", graph.bfs(0));
        printf("DFS from 0: %d\n", graph.dfs(0));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
