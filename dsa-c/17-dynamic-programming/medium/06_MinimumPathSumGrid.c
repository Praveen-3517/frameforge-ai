/**
 * Problem: Minimum Path Sum (LeetCode 64)
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an m x n grid filled with non-negative numbers, find a path from top left
 * to bottom right, which minimizes the sum of all numbers along its path.
 * You can only move either down or right at any point in time.
 * 
 * Approach:
 * 1D Space-Optimized Dynamic Programming:
 * dp[c] = grid[r][c] + min(dp[c] (from above), dp[c - 1] (from left)).
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(N) where N is number of columns.
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

int minPathSum(int** grid) {
        int m = n;
        int n = grid[0].length;
        int* dp = (int*)malloc((n) * sizeof(int));

        dp[0] = grid[0][0];
        for (int c = 1; c < n; c++) {
            dp[c] = dp[c - 1] + grid[0][c];
        }

        for (int r = 1; r < m; r++) {
            dp[0] += grid[r][0];
            for (int c = 1; c < n; c++) {
                dp[c] = grid[r][c] + MIN(dp[c], dp[c - 1]);
            }
        }

        return dp[n - 1];
    }

    int main(void) {
        int** grid1 = {
            {1, 3, 1},
            {1, 5, 1},
            {4, 2, 1}
        };
        printf("Min path sum 1: " + minPathSum(grid1) + " (Expected: 7)\n");

        int** grid2 = {
            {1, 2, 3},
            {4, 5, 6}
        };
        printf("Min path sum 2: " + minPathSum(grid2) + " (Expected: 12)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
