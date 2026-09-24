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

int*> kosarajuSCC(int n, int*> adj) {
        // Step 1: DFS to get finish time ordering
        bool[] visited = (bool*)malloc((n) * sizeof(bool));
        Deque<int> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                fillOrder(i, adj, visited, stack);
            }
        }

        // Step 2: Reverse graph
        int*> transpose = new ArrayList<>(n);
        for (int i = 0; i < n; i++) transpose.add(new ArrayList<>());

        for (int u = 0; u < n; u++) {
            for (int v : adj.get(u)) {
                transpose.get(v).add(u);
            }
        }

        // Step 3: DFS on transposed graph in order of stack
        java.util.Arrays.fill(visited, false);
        int*> sccs = new ArrayList<>();

        while (!stack.isEmpty()) {
            int u = stack.pop();
            if (!visited[u]) {
                int* component = new ArrayList<>();
                dfsCollect(u, transpose, visited, component);
                sccs.add(component);
            }
        }

        return sccs;
    }

    static void fillOrder(int u, int*> adj, bool[] visited, Deque<int> stack) {
        visited[u] = true;
        for (int v : adj.get(u)) {
            if (!visited[v]) {
                fillOrder(v, adj, visited, stack);
            }
        }
        stack.push(u);
    }

    static void dfsCollect(int u, int*> transpose, bool[] visited, int* component) {
        visited[u] = true;
        component.add(u);
        for (int v : transpose.get(u)) {
            if (!visited[v]) {
                dfsCollect(v, transpose, visited, component);
            }
        }
    }

    int main(void) {
        int n = 5;
        int*> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        // Graph: 1 -> 0, 0 -> 2, 2 -> 1, 0 -> 3, 3 -> 4
        adj.get(1).add(0);
        adj.get(0).add(2);
        adj.get(2).add(1);
        adj.get(0).add(3);
        adj.get(3).add(4);

        int*> sccs = kosarajuSCC(n, adj);
        printf("Strongly Connected Components: %d\n", sccs);
        // Expected SCCs: [0, 1, 2], [3], [4]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
