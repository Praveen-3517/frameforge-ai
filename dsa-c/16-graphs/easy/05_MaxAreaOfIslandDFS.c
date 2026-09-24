/**
 * Problem: Max Area of Island (LeetCode 695)
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally. The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 * 
 * Approach:
 * Depth-First Search (DFS):
 * For every cell (r, c) == 1:
 * - Sink cell (set grid[r][c] = 0).
 * - Return 1 + dfs(up) + dfs(down) + dfs(left) + dfs(right).
 * - Maintain maximum area across all components.
 * 
 * Time Complexity: O(M * N) where M is rows, N is columns.
 * Space Complexity: O(M * N) worst case recursion stack.
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

int maxAreaOfIsland(int** grid) {
        if (grid == NULL || n == 0) return 0;

        int maxArea = 0;
        int rows = n;
        int cols = grid[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    int area = dfs(grid, r, c);
                    maxArea = MAX(maxArea, area);
                }
            }
        }

        return maxArea;
    }

    static int dfs(int** grid, int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= grid[0].length || grid[r][c] != 1) {
            return 0;
        }

        grid[r][c] = 0; // mark visited

        return 1 
            + dfs(grid, r + 1, c) 
            + dfs(grid, r - 1, c) 
            + dfs(grid, r, c + 1) 
            + dfs(grid, r, c - 1);
    }

    int main(void) {
        int** grid = {
            {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
        };

        printf("Max Area: " + maxAreaOfIsland(grid) + " (Expected: 6)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
