/**
 * Problem: Unique Paths (LeetCode 62)
 * Asked in: Amazon, Google, Microsoft, Facebook
 * 
 * There is a robot on an m x n grid. The robot is initially located at top-left corner (0, 0)
 * and attempts to move to bottom-right corner (m - 1, n - 1). The robot can only move either down or right.
 * Return the number of possible unique paths.
 * 
 * Approach:
 * Grid DP with 1D Space Optimization:
 * dp[r][c] = dp[r - 1][c] + dp[r][c - 1]
 * We can optimize space to a single array of length n initialized to 1:
 * For each row from 1 to m - 1:
 *   For col from 1 to n - 1:
 *     dp[col] += dp[col - 1]
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(N)
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

int uniquePaths(int m, int n) {
        int* dp = (int*)malloc((n) * sizeof(int));
        Arrays.fill(dp, 1);

        for (int r = 1; r < m; r++) {
            for (int c = 1; c < n; c++) {
                dp[c] += dp[c - 1];
            }
        }

        return dp[n - 1];
    }

    int main(void) {
        printf("Unique paths (3, 7): " + uniquePaths(3, 7) + " (Expected: 28)\n");
        printf("Unique paths (3, 2): " + uniquePaths(3, 2) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
