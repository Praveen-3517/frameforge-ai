/**
 * Problem: Redundant Connection (LeetCode 684)
 * Asked in: Google, Amazon, Facebook
 * 
 * A tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n,
 * with one additional edge added.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
 * 
 * Approach:
 * Disjoint Set Union (DSU):
 * - Initialize DSU with n + 1 elements.
 * - Iterate through each edge [u, v]:
 *   - If find(u) == find(v), u and v are ALREADY connected! Adding this edge creates a cycle.
 *     Thus, [u, v] is the redundant edge.
 *   - Otherwise, union(u, v).
 * 
 * Time Complexity: O(N * alpha(N))
 * Space Complexity: O(N) for DSU parent array.
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

int* findRedundantConnection(int** edges) {
        int n = n;
        int* parent = (int*)malloc((n + 1) * sizeof(int));
        for (int i = 1; i <= n; i++) parent[i] = i;

        for (int* edge : edges) {
            int u = edge[0];
            int v = edge[1];

            int rootU = find(parent, u);
            int rootV = find(parent, v);

            if (rootU == rootV) {
                return edge; // Found the cycle-forming edge
            }
            parent[rootU] = rootV;
        }

        return (int*)malloc((0) * sizeof(int));
    }

    static int find(int* parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }

    int main(void) {
        int** edges1 = {{1, 2}, {1, 3}, {2, 3}};
        printf("Redundant edge: " + "[array]") + " (Expected: [2, 3])\n");

        int** edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
        printf("Redundant edge: " + "[array]") + " (Expected: [1, 4])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
