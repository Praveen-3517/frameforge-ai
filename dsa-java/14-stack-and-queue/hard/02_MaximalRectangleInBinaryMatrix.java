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

import java.util.ArrayDeque;
import java.util.Deque;

class MaximalRectangleInBinaryMatrix {

    /**
     * Approach:
     * Dynamic 2D Histogram Reduction:
     * - Maintain a running 1D heights array of size cols.
     * - For each row:
     *   - If matrix[r][c] == '1', heights[c]++ (extends vertical bar height).
     *   - Else heights[c] = 0 (resets baseline).
     *   - Call Largest Rectangle in Histogram subroutine on the heights array!
     */
    public static int maximalRectangle(char[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) return 0;

        int cols = matrix[0].length;
        int[] heights = new int[cols];
        int maxArea = 0;

        for (char[] row : matrix) {
            for (int c = 0; c < cols; c++) {
                if (row[c] == '1') {
                    heights[c]++;
                } else {
                    heights[c] = 0;
                }
            }

            maxArea = Math.max(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }

    private static int largestRectangleArea(int[] heights) {
        int n = heights.length;
        Deque<Integer> stack = new ArrayDeque<>();
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            int currentHeight = (i == n) ? 0 : heights[i];

            while (!stack.isEmpty() && currentHeight < heights[stack.peek()]) {
                int h = heights[stack.pop()];
                int w = stack.isEmpty() ? i : (i - stack.peek() - 1);
                maxArea = Math.max(maxArea, h * w);
            }

            stack.push(i);
        }

        return maxArea;
    }

    public static void main(String[] args) {
        char[][] matrix = {
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'}
        };

        System.out.println("Maximal Rectangle Area: " + maximalRectangle(matrix) + " (Expected: 6)");
    }
}

/*
 * Time Complexity: O(R * C) where R is rows count and C is cols count.
 * Space Complexity: O(C) for the 1D running heights array and monotonic stack.
 */
