/*
 * Problem Statement:
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 * (LeetCode 85: Maximal Rectangle)
 * 
 * Example:
 * matrix = [
 *   ["1","0","1","0","0"],
 *   ["1","0","1","1","1"],
 *   ["1","1","1","1","1"],
 *   ["1","0","0","1","0"]
 * ]
 * Output: 6
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Apple
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

/**
     * Approach:
     * Dynamic 2D Histogram Reduction:
     * - Maintain a running 1D heights array of size cols.
     * - For each row:
     *   - If matrix[r][c] == '1', heights[c]++ (extends vertical bar height).
     *   - Else heights[c] = 0 (resets baseline).
     *   - Call Largest Rectangle in Histogram subroutine on the heights array!
     */
    int maximalRectangle(char** matrix) {
        if (matrix == NULL || n == 0 || matrix[0].length == 0) return 0;

        int cols = matrix[0].length;
        int* heights = (int*)malloc((cols) * sizeof(int));
        int maxArea = 0;

        for (char* row : matrix) {
            for (int c = 0; c < cols; c++) {
                if (row[c] == '1') {
                    heights[c]++;
                } else {
                    heights[c] = 0;
                }
            }

            maxArea = MAX(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }

    static int largestRectangleArea(int* heights) {
        int n = n;
        Deque<int> stack = new ArrayDeque<>();
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            int currentHeight = (i == n) ? 0 : heights[i];

            while (!stack.isEmpty() && currentHeight < heights[stack.peek()]) {
                int h = heights[stack.pop()];
                int w = stack.isEmpty() ? i : (i - stack.peek() - 1);
                maxArea = MAX(maxArea, h * w);
            }

            stack.push(i);
        }

        return maxArea;
    }

    int main(void) {
        char** matrix = {
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'}
        };

        printf("Maximal Rectangle Area: " + maximalRectangle(matrix) + " (Expected: 6)\n");
        return 0;
}

/*
 * Time Complexity: O(R * C) where R is rows count and C is cols count.
 * Space Complexity: O(C) for the 1D running heights array and monotonic stack.
 */
