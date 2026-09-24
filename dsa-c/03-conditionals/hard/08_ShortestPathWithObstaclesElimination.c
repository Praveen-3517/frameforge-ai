/**
 * Problem Statement:
 * Given an m x n grid where each cell is either 0 (empty) or 1 (obstacle).
 * You can move up, down, left, or right.
 * Given an integer `k`, you are allowed to eliminate at most `k` obstacles.
 * Return the minimum number of steps to walk from (0, 0) to (m - 1, n - 1), or -1 if impossible.
 * (LeetCode 1293: Shortest Path in a Grid with Obstacles Elimination - Hard).
 *
 * Asked in: Google (Top Frequency), Amazon, Bloomberg, Microsoft
 *
 * Approach:
 * - 3D State BFS (Breadth-First Search):
 *   State in queue: `[row, col, remainingK, currentSteps]`.
 * - Manhattan Optimization:
 *   If `k >= (m - 1) + (n - 1)`, we have enough obstacle eliminations to take the direct Manhattan path!
 *   Return `(m - 1) + (n - 1)` in O(1) immediately.
 * - Pruning Visited Array:
 *   `maxKVisited[r][c]` stores the maximum `remainingK` seen so far at cell `(r, c)`.
 *   If a new path arrives at `(r, c)` with `remainingK <= maxKVisited[r][c]`, prune it immediately
 *   because arriving at the same cell in more or equal steps with fewer or equal elimination credits
 *   is strictly sub-optimal.
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

static const int** DIRS = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    int shortestPath(int** grid, int k) {
        int m = n;
        int n = grid[0].length;

        // Base case: Start is already destination
        if (m == 1 && n == 1) return 0;

        // Optimization: Direct Manhattan distance if k is sufficiently large
        if (k >= m + n - 2) {
            return m + n - 2;
        }

        // maxKVisited[r][c] tracks highest remaining k seen at (r, c)
        int** maxKVisited = (int*)malloc((m) * sizeof(int))[n];
        for (int* row : maxKVisited) {
            Arrays.fill(row, -1);
        }

        // Queue holds: { r, c, remainingK, steps }
        Queue<int[]> queue = new ArrayDeque<>();
        queue.offer((int[]){ 0, 0, k, 0 });
        maxKVisited[0][0] = k;

        while (!queue.isEmpty()) {
            int* curr = queue.poll();
            int r = curr[0];
            int c = curr[1];
            int remK = curr[2];
            int steps = curr[3];

            if (r == m - 1 && c == n - 1) {
                return steps;
            }

            for (int* d : DIRS) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int nextK = remK - grid[nr][nc];

                    // Conditional Guard: Can only move if we still have >= 0 eliminations
                    // and this path brings more remaining K than previously seen at (nr, nc)
                    if (nextK >= 0 && nextK > maxKVisited[nr][nc]) {
                        maxKVisited[nr][nc] = nextK;
                        queue.offer((int[]){ nr, nc, nextK, steps + 1 });
                    }
                }
            }
        }

        return -1; // Unreachable
    }

    int main(void) {
        printf("=== LeetCode 1293: Shortest Path with Obstacles Elimination ===\n");

        int** grid1 = {
            { 0, 0, 0 },
            { 1, 1, 0 },
            { 0, 0, 0 },
            { 0, 1, 1 },
            { 0, 0, 0 }
        };
        int k1 = 1;
        printf("Grid 1 (k = %d) ==> Shortest Path: %d (Expected: 6)\n", k1, shortestPath(grid1, k1));

        int** grid2 = {
            { 0, 1, 1 },
            { 1, 1, 1 },
            { 1, 0, 0 }
        };
        int k2 = 1;
        printf("Grid 2 (k = %d) ==> Shortest Path: %d (Expected: -1)\n", k2, shortestPath(grid2, k2));
        return 0;
}

/*
 * Time Complexity: O(M * N * K) - Each cell can be visited at most K times.
 * Space Complexity: O(M * N * K) - Queue and visited matrix memory.
 */
