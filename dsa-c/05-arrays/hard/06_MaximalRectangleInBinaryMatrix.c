/**
 * Problem Statement:
 * Given a `rows x cols` binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 * (LeetCode 85: Maximal Rectangle - Hard).
 *
 * Example:
 * matrix = [
 *   ["1","0","1","0","0"],
 *   ["1","0","1","1","1"],
 *   ["1","1","1","1","1"],
 *   ["1","0","0","1","0"]
 * ]
 * Output: 6 (the 2x3 rectangle of 1s in rows 1-2, cols 2-4)
 *
 * Asked in: Google, Amazon, Microsoft, Facebook / Meta, Apple
 *
 * Approach:
 * - Dynamic Histogram Reduction (O(Rows * Cols) Time, O(Cols) Space):
 *   Convert the 2D problem into a series of 1D histogram problems (LeetCode 84)!
 *   - Maintain a 1D array `heights` of size `cols`.
 *   - For each row `r`:
 *     - If `matrix[r][c] == '1'`, increment `heights[c] += 1`.
 *     - If `matrix[r][c] == '0'`, reset `heights[c] = 0` (breaks the vertical pillar of 1s).
 *     - Run the Monotonic Stack largest rectangle algorithm on `heights`.
 *     - Update `maxArea = Math.max(maxArea, rowMaxArea)`.
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

int maximalRectangle(char** matrix) {
        if (matrix == NULL || n == 0 || matrix[0].length == 0) return 0;

        int rows = n;
        int cols = matrix[0].length;
        int* heights = (int*)malloc((cols) * sizeof(int));
        int maxArea = 0;

        for (int r = 0; r < rows; r++) {
            // Update histogram heights for current row
            for (int c = 0; c < cols; c++) {
                if (matrix[r][c] == '1') {
                    heights[c] += 1;
                } else {
                    heights[c] = 0;
                }
            }

            // Compute max rectangle in current histogram
            maxArea = MAX(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }

    static int largestRectangleArea(int* heights) {
        int n = n;
        Deque<int> stack = new ArrayDeque<>();
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            int currentH = (i == n) ? 0 : heights[i];

            while (!stack.isEmpty() && currentH < heights[stack.peek()]) {
                int h = heights[stack.pop()];
                int w = stack.isEmpty() ? i : (i - stack.peek() - 1);
                maxArea = MAX(maxArea, h * w);
            }

            stack.push(i);
        }

        return maxArea;
    }

    int main(void) {
        printf("=== LeetCode 85: Maximal Rectangle in Binary Matrix ===\n");

        char** matrix = {
            { '1', '0', '1', '0', '0' },
            { '1', '0', '1', '1', '1' },
            { '1', '1', '1', '1', '1' },
            { '1', '0', '0', '1', '0' }
        };

        int maxRec = maximalRectangle(matrix);
        printf("Maximal Rectangle Area of 1s: %d (Expected: 6)\n", maxRec);
        return 0;
}

/*
 * Time Complexity: O(R * C) - Each cell is processed once per row in histogram calculation.
 * Space Complexity: O(C) - Heights array and stack sized to number of columns.
 */
