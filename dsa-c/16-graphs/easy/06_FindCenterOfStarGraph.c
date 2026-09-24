/**
 * Problem: Find Center of Star Graph (LeetCode 1791)
 * Asked in: Amazon, Microsoft
 * 
 * There is an undirected star graph consisting of n nodes labeled from 1 to n.
 * A star graph is a graph where there is one center node and exactly n - 1 edges
 * that connect the center node with every other node.
 * Given a 2D integer array edges where each edges[i] = [ui, vi], return the center.
 * 
 * Approach:
 * Since the center node is connected to every other node, it MUST be present in EVERY edge.
 * Thus, we only need to compare the first two edges: edges[0] and edges[1].
 * Whichever vertex is shared between these two edges is guaranteed to be the center!
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
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

int findCenter(int** edges) {
        // If edges[0][0] is present in edges[1], it's the center; otherwise edges[0][1] is.
        if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) {
            return edges[0][0];
        }
        return edges[0][1];
    }

    int main(void) {
        int** edges1 = {{1, 2}, {2, 3}, {4, 2}};
        printf("Center: " + findCenter(edges1) + " (Expected: 2)\n");

        int** edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};
        printf("Center: " + findCenter(edges2) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
