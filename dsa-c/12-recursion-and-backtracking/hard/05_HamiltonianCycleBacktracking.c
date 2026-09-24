/*
 * Problem Statement:
 * A Hamiltonian cycle in an undirected graph is a closed path that visits every vertex
 * exactly once and returns to the starting vertex.
 * Given an adjacency matrix, find a Hamiltonian cycle if one exists.
 * (Classic NP-Complete Graph Problem)
 * 
 * Asked in: Google, Amazon, Cisco
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

bool findHamiltonianCycle(int** graph, int n) {
        int* path = (int*)malloc((n) * sizeof(int));
        Arrays.fill(path, -1);

        // Put vertex 0 as first vertex in cycle
        path[0] = 0;

        if (!solve(1, graph, path, n)) {
            printf("No Hamiltonian Cycle exists for this graph.\n");
            return false;
        }

        printf("%s", "Hamiltonian Cycle found: ");
        for (int v : path) printf("%s", v + " -> ");
        printf("%d\n", path[0]);
        return true;
    }

    static bool solve(int pos, int** graph, int* path, int n) {
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

    static bool isSafe(int v, int** graph, int* path, int pos) {
        // Must have an edge from previous vertex
        if (graph[path[pos - 1]][v] == 0) return false;

        // Must not be already visited
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) return false;
        }

        return true;
    }

    int main(void) {
        int n = 5;
        int** graph1 = {
            {0, 1, 0, 1, 0},
            {1, 0, 1, 1, 1},
            {0, 1, 0, 0, 1},
            {1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0}
        };

        printf("--- Hamiltonian Cycle Solver ---\n");
        findHamiltonianCycle(graph1, n);
        return 0;
}

/*
 * Time Complexity: O(N!) in worst case.
 * Space Complexity: O(N) path array and call stack.
 */
