/**
 * Problem: Trapping Rain Water II (LeetCode 407)
 * Asked in: Google, Amazon, Twitter
 * 
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map,
 * return the volume of water it can trap after raining.
 * 
 * Approach:
 * PriorityQueue / Min-Heap Boundary Inward Shrinking:
 * - The water level is determined by the LOWEST boundary wall currently surrounding the inner cells.
 * 1. Push all outer boundary cells into a Min-Heap and mark them visited.
 * 2. While heap is not empty:
 *    - Poll the lowest boundary cell [r, c, h].
 *    - Check all 4 unvisited neighbors [nr, nc]:
 *      - If neighbor's height < h: trappedWater += (h - neighborHeight).
 *      - Offer neighbor into heap with effective boundary height = max(h, neighborHeight).
 *      - Mark neighbor visited.
 * 
 * Time Complexity: O(M * N log(M * N))
 * Space Complexity: O(M * N)
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

int trapRainWater(int** heightMap) {
        if (heightMap == NULL || n <= 2 || heightMap[0].length <= 2) {
            return 0;
        }

        int rows = n;
        int cols = heightMap[0].length;
        bool[][] visited = (bool*)malloc((rows) * sizeof(bool))[cols];

        // Min-heap: [row, col, height]
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[2]));

        // Add first and last columns to heap
        for (int r = 0; r < rows; r++) {
            minHeap.offer((int[]){r, 0, heightMap[r][0]});
            minHeap.offer((int[]){r, cols - 1, heightMap[r][cols - 1]});
            visited[r][0] = true;
            visited[r][cols - 1] = true;
        }

        // Add first and last rows to heap
        for (int c = 1; c < cols - 1; c++) {
            minHeap.offer((int[]){0, c, heightMap[0][c]});
            minHeap.offer((int[]){rows - 1, c, heightMap[rows - 1][c]});
            visited[0][c] = true;
            visited[rows - 1][c] = true;
        }

        int totalWater = 0;
        int* dr = {-1, 1, 0, 0};
        int* dc = {0, 0, -1, 1};

        while (!minHeap.isEmpty()) {
            int* cell = minHeap.poll();
            int r = cell[0];
            int c = cell[1];
            int h = cell[2];

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    totalWater += MAX(0, h - heightMap[nr][nc]);
                    minHeap.offer((int[]){nr, nc, MAX(h, heightMap[nr][nc])});
                }
            }
        }

        return totalWater;
    }

    int main(void) {
        int** heightMap = {
            {1, 4, 3, 1, 3, 2},
            {3, 2, 1, 3, 2, 4},
            {2, 3, 3, 2, 3, 1}
        };

        printf("Trapped 3D water: " + trapRainWater(heightMap) + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
