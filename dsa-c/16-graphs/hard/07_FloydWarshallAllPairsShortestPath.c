/**
 * Problem: Floyd-Warshall All-Pairs Shortest Path Algorithm
 * Asked in: Google, Amazon, Adobe, Oracle
 * 
 * Given an adjacency matrix graph with V vertices, find the shortest distances
 * between every pair of vertices.
 * 
 * Approach:
 * Dynamic Programming:
 * Let dist[i][j] be the shortest distance from vertex i to vertex j using intermediate
 * vertices from set {0, 1, ..., k}.
 * State Transition:
 * dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 * Negative Cycle Check:
 * If any dist[i][i] < 0 after completion, a negative weight cycle exists.
 * 
 * Time Complexity: O(V^3) with 3 nested loops.
 * Space Complexity: O(V^2) for distance matrix.
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

static const int INF = 1_000_000_000;

    int** floydWarshall(int** graph) {
        int n = n;
        int** dist = (int*)malloc((n) * sizeof(int))[n];

        for (int i = 0; i < n; i++) {
            dist[i] = Arrays.copyOf(graph[i], n);
        }

        // Try every vertex k as an intermediate step
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Check for negative cycle
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                printf("Graph contains negative weight cycle!\n");
                return NULL;
            }
        }

        return dist;
    }

    int main(void) {
        int** graph = {
            {0, 5, INF, 10},
            {INF, 0, 3, INF},
            {INF, INF, 0, 1},
            {INF, INF, INF, 0}
        };

        int** dist = floydWarshall(graph);
        printf("All Pairs Shortest Paths:\n");
        for (int* row : dist) {
            printf("[array]\n");
        }
        // Expected:
        // [0, 5, 8, 9]
        // [INF, 0, 3, 4]
        // [INF, INF, 0, 1]
        // [INF, INF, INF, 0]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
