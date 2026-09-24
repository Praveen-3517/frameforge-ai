/**
 * Problem: Rotting Oranges (LeetCode 994)
 * Asked in: Amazon, Microsoft, Google, Bloomberg
 * 
 * You are given an m x n grid containing values:
 * - 0: Empty cell
 * - 1: Fresh orange
 * - 2: Rotten orange
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange.
 * If this is impossible, return -1.
 * 
 * Approach:
 * Multi-Source Breadth-First Search (BFS):
 * 1. Count fresh oranges.
 * 2. Enqueue all initial rotten oranges (cells with value 2) at time 0.
 * 3. Process BFS layer by layer (minute by minute):
 *    - Expand 4 directions; if fresh orange (1) found:
 *      - Turn it rotten (2), decrement freshCount, enqueue it.
 * 4. Return minutes if freshCount == 0, else -1.
 * 
 * Time Complexity: O(M * N) visiting each cell once.
 * Space Complexity: O(M * N) queue space.
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

int orangesRotting(int** grid) {
        int rows = n;
        int cols = grid[0].length;
        int freshCount = 0;

        Queue<int[]> queue = new ArrayDeque<>();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 2) {
                    queue.offer((int[]){r, c});
                } else if (grid[r][c] == 1) {
                    freshCount++;
                }
            }
        }

        if (freshCount == 0) return 0;

        int minutes = 0;
        int* dr = {-1, 1, 0, 0};
        int* dc = {0, 0, -1, 1};

        while (!queue.isEmpty() && freshCount > 0) {
            int size = queue.size();
            minutes++;

            for (int i = 0; i < size; i++) {
                int* curr = queue.poll();
                int r = curr[0];
                int c = curr[1];

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // rotten
                        freshCount--;
                        queue.offer((int[]){nr, nc});
                    }
                }
            }
        }

        return freshCount == 0 ? minutes : -1;
    }

    int main(void) {
        int** grid1 = {
            {2, 1, 1},
            {1, 1, 0},
            {0, 1, 1}
        };
        printf("Minutes to rot 1: " + orangesRotting(grid1) + " (Expected: 4)\n");

        int** grid2 = {
            {2, 1, 1},
            {0, 1, 1},
            {1, 0, 1}
        };
        printf("Minutes to rot 2: " + orangesRotting(grid2) + " (Expected: -1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
