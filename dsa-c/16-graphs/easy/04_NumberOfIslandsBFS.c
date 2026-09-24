/**
 * Problem: Number of Islands (LeetCode 200)
 * Asked in: Amazon, Google, Microsoft, Bloomberg, Meta
 * 
 * Given an m x n 2D binary grid grid which represents a map of '1's (land)
 * and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands
 * horizontally or vertically.
 * 
 * Approach:
 * Breadth-First Search (BFS):
 * 1. Iterate through each cell (r, c).
 * 2. When '1' is found, increment islandCount, and launch BFS to mark all connected '1's as '0'.
 * 3. BFS uses a queue of encoded coordinates (r * cols + c) to save space.
 * 
 * Time Complexity: O(M * N) since each cell is visited and enqueued at most once.
 * Space Complexity: O(min(M, N)) for BFS queue size.
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

int numIslands(char** grid) {
        if (grid == NULL || n == 0) return 0;

        int rows = n;
        int cols = grid[0].length;
        int islandCount = 0;

        int* dr = {-1, 1, 0, 0};
        int* dc = {0, 0, -1, 1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    islandCount++;
                    // BFS to sink current island
                    Queue<int> queue = new ArrayDeque<>();
                    queue.offer(r * cols + c);
                    grid[r][c] = '0'; // mark visited

                    while (!queue.isEmpty()) {
                        int pos = queue.poll();
                        int currR = pos / cols;
                        int currC = pos % cols;

                        for (int d = 0; d < 4; d++) {
                            int nr = currR + dr[d];
                            int nc = currC + dc[d];

                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == '1') {
                                grid[nr][nc] = '0';
                                queue.offer(nr * cols + nc);
                            }
                        }
                    }
                }
            }
        }

        return islandCount;
    }

    int main(void) {
        char** grid1 = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        };
        printf("Islands in grid 1: " + numIslands(grid1) + " (Expected: 1)\n");

        char** grid2 = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        };
        printf("Islands in grid 2: " + numIslands(grid2) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
