/*
 * Problem Statement:
 * Given an array of integers heights representing the histogram's bar height where the
 * width of each bar is 1, return the area of the largest rectangle in the histogram.
 * (LeetCode 84: Largest Rectangle in Histogram)
 * 
 * Example:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10 (Rectangle formed by heights 5 and 6 with width 2 -> 5 * 2 = 10)
 * 
 * Asked in: Amazon, Google, Facebook/Meta, Apple, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class LargestRectangleInHistogramMonotonicStack {

    /**
     * Approach:
     * Monotonic Increasing Stack of Indices:
     * - We maintain a stack of indices where heights are strictly increasing.
     * - When a smaller height arrives at index i, pop indices from stack:
     *   - The popped index 'hIdx' is the height of the rectangle: h = heights[hIdx].
     *   - The right boundary is i (first smaller bar to right).
     *   - The left boundary is stack.peek() (first smaller bar to left).
     *   - width = stack.isEmpty() ? i : (i - stack.peek() - 1).
     *   - area = h * width.
     */
    public static int largestRectangleArea(int[] heights) {
        int n = heights.length;
        Deque<Integer> stack = new ArrayDeque<>();
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            // Virtual 0 height at index n forces stack flushing
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
        int[] heights1 = {2, 1, 5, 6, 2, 3};
        System.out.println("Heights: " + Arrays.toString(heights1));
        System.out.println("Largest Rectangle Area: " + largestRectangleArea(heights1) + " (Expected: 10)");

        int[] heights2 = {2, 4};
        System.out.println("\nHeights: " + Arrays.toString(heights2));
        System.out.println("Largest Rectangle Area: " + largestRectangleArea(heights2) + " (Expected: 4)");
    }
}

/*
 * Time Complexity: O(N) - Each bar index pushed and popped from stack at most once.
 * Space Complexity: O(N) monotonic stack storage.
 */
