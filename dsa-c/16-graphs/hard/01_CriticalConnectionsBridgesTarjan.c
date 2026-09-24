/**
 * Problem: Critical Connections in a Network / Bridges (LeetCode 1192)
 * Asked in: Amazon, Google, Facebook
 * 
 * There are n servers numbered 0 to n - 1 connected by undirected server-to-server connections.
 * A critical connection is a connection that, if removed, will make some servers unable
 * to reach other servers (a bridge). Return all critical connections in the network.
 * 
 * Approach:
 * Tarjan's Bridge-Finding Algorithm (DFS):
 * Maintain two arrays:
 * - tin[u]: discovery timestamp of node u.
 * - low[u]: lowest discovery timestamp reachable from u using backward edges.
 * For each neighbor v of u (excluding parent):
 * - If v is unvisited:
 *   - Recurse dfs(v, u).
 *   - low[u] = min(low[u], low[v]).
 *   - If low[v] > tin[u], then edge (u, v) is a CRITICAL BRIDGE! (v cannot reach u or ancestors of u without this edge).
 * - Else (back-edge to already visited node):
 *   - low[u] = min(low[u], tin[v]).
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
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

static int timer;

    int*> criticalConnections(int n, int*> connections) {
        int*> adj = new ArrayList<>(n);
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());

        for (int* edge : connections) {
            int u = edge.get(0);
            int v = edge.get(1);
            adj.get(u).add(v);
            adj.get(v).add(u);
        }

        int* tin = (int*)malloc((n) * sizeof(int));
        int* low = (int*)malloc((n) * sizeof(int));
        bool[] visited = (bool*)malloc((n) * sizeof(bool));
        int*> bridges = new ArrayList<>();
        timer = 0;

        dfs(0, -1, adj, tin, low, visited, bridges);

        return bridges;
    }

    static void dfs(int u, int parent, int*> adj, int* tin, int* low, bool[] visited, int*> bridges) {
        visited[u] = true;
        tin[u] = low[u] = ++timer;

        for (int v : adj.get(u)) {
            if (v == parent) continue;

            if (visited[v]) {
                low[u] = MIN(low[u], tin[v]);
            } else {
                dfs(v, u, adj, tin, low, visited, bridges);
                low[u] = MIN(low[u], low[v]);

                if (low[v] > tin[u]) {
                    bridges.add(Arrays.asList(u, v));
                }
            }
        }
    }

    int main(void) {
        int*> connections = new ArrayList<>();
        connections.add(Arrays.asList(0, 1));
        connections.add(Arrays.asList(1, 2));
        connections.add(Arrays.asList(2, 0));
        connections.add(Arrays.asList(1, 3));

        int*> bridges = criticalConnections(4, connections);
        printf("Bridges: " + bridges + " (Expected: [[1, 3]])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
