/**
 * Problem: Campus Bikes II / Worker to Bike Assignment - Optimal Cost (LeetCode 1066)
 * Asked in: Google, Amazon
 * 
 * On a campus represented as a 2D grid, there are n workers and m bikes.
 * Assign each worker to a unique bike to minimize the total Manhattan distance sum.
 * Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.
 * 
 * Approach - Bitmask DP over Bike Assignments:
 * dp[mask] = minimum cost to assign workers 0..(popcount(mask)-1) to bikes indicated by mask.
 * The number of assigned workers = popcount(mask).
 * 
 * For each mask, let workerIdx = Integer.bitCount(mask):
 *   For each bit j set in (all bikes) but NOT in mask:
 *     dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + dist(worker workerIdx, bike j))
 * 
 * Time Complexity: O(2^M * M) where M = number of bikes.
 * Space Complexity: O(2^M)
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

static int manhattanDist(int* worker, int* bike) {
        return abs(worker[0] - bike[0]) + abs(worker[1] - bike[1]);
    }

    int assignBikes(int** workers, int** bikes) {
        int n = n;
        int m = n;
        int* dp = (int*)malloc((1 << m) * sizeof(int));
        java.util.Arrays.fill(dp, INT_MAX);
        dp[0] = 0;

        int minCost = INT_MAX;

        for (int mask = 0; mask < (1 << m); mask++) {
            if (dp[mask] == INT_MAX) continue;

            int workerIdx = int.bitCount(mask);
            if (workerIdx == n) {
                minCost = MIN(minCost, dp[mask]);
                continue;
            }

            for (int j = 0; j < m; j++) {
                if ((mask & (1 << j)) != 0) continue; // bike already assigned
                int newMask = mask | (1 << j);
                int newCost = dp[mask] + manhattanDist(workers[workerIdx], bikes[j]);
                dp[newMask] = MIN(dp[newMask], newCost);
            }
        }

        return minCost;
    }

    int main(void) {
        int** workers1 = {{0, 0}, {2, 1}};
        int** bikes1 = {{1, 2}, {3, 3}};
        printf("Min assignment cost: " + assignBikes(workers1, bikes1) + " (Expected: 6)\n");
        // Worker 0 -> Bike 0: |0-1|+|0-2|=3, Worker 1 -> Bike 1: |2-3|+|1-3|=3, Total=6

        int** workers2 = {{0, 0}, {1, 1}, {2, 0}};
        int** bikes2 = {{1, 0}, {2, 2}, {2, 1}};
        printf("Min assignment cost: " + assignBikes(workers2, bikes2) + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
