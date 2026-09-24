/**
 * Problem: Find if Path Exists in Graph (LeetCode 1971)
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * There is a bi-directional graph with n vertices, where each vertex is labeled
 * from 0 to n - 1. Given 2D array edges, source and destination, determine if there
 * is a valid path that exists from source to destination.
 * 
 * Approach:
 * Breadth-First Search (BFS):
 * 1. Build adjacency list from edges.
 * 2. Start BFS queue from source, mark source visited.
 * 3. If destination is dequeued, return true immediately.
 * 4. If queue empties without reaching destination, return false.
 * 
 * Time Complexity: O(V + E) where V = n and E = edges.length.
 * Space Complexity: O(V + E) for adjacency list and BFS queue.
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

bool validPath(int n, int** edges, int source, int destination) {
        if (source == destination) return true;

        int*> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        for (int* edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        bool[] visited = (bool*)malloc((n) * sizeof(bool));
        Queue<int> queue = new ArrayDeque<>();

        visited[source] = true;
        queue.offer(source);

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            if (curr == destination) return true;

            for (int neighbor : adj.get(curr)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(neighbor);
                }
            }
        }

        return false;
    }

    int main(void) {
        int n1 = 3;
        int** edges1 = {{0, 1}, {1, 2}, {2, 0}};
        printf("Path 0->2 exists: " + validPath(n1, edges1, 0, 2) + " (Expected: true)\n");

        int n2 = 6;
        int** edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
        printf("Path 0->5 exists: " + validPath(n2, edges2, 0, 5) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
