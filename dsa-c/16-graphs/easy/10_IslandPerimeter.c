/**
 * Problem: Island Perimeter (LeetCode 463)
 * Asked in: Facebook, Google, Amazon, Apple
 * 
 * You are given row x col grid representing a map where grid[i][j] = 1 represents
 * land and grid[i][j] = 0 represents water. Grid cells are connected horizontally/vertically.
 * Determine the perimeter of the island.
 * 
 * Approach:
 * Counting edges:
 * - Each land cell initially contributes 4 edges.
 * - For each land cell, check its top and left neighbor.
 * - If top neighbor is land, both share an edge -> subtract 2.
 * - If left neighbor is land, both share an edge -> subtract 2.
 * 
 * Time Complexity: O(M * N) single pass.
 * Space Complexity: O(1) auxiliary space.
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

int islandPerimeter(int** grid) {
        int rows = n;
        int cols = grid[0].length;
        int perimeter = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    perimeter += 4;

                    // Check upper neighbor
                    if (r > 0 && grid[r - 1][c] == 1) {
                        perimeter -= 2;
                    }
                    // Check left neighbor
                    if (c > 0 && grid[r][c - 1] == 1) {
                        perimeter -= 2;
                    }
                }
            }
        }

        return perimeter;
    }

    int main(void) {
        int** grid = {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0}
        };

        printf("Island Perimeter: " + islandPerimeter(grid) + " (Expected: 16)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
