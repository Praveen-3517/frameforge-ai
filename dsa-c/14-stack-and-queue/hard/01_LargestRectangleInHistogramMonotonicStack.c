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
     * Monotonic Increasing Stack of Indices:
     * - We maintain a stack of indices where heights are strictly increasing.
     * - When a smaller height arrives at index i, pop indices from stack:
     *   - The popped index 'hIdx' is the height of the rectangle: h = heights[hIdx].
     *   - The right boundary is i (first smaller bar to right).
     *   - The left boundary is stack.peek() (first smaller bar to left).
     *   - width = stack.isEmpty() ? i : (i - stack.peek() - 1).
     *   - area = h * width.
     */
    int largestRectangleArea(int* heights) {
        int n = n;
        Deque<int> stack = new ArrayDeque<>();
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            // Virtual 0 height at index n forces stack flushing
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
        int* heights1 = {2, 1, 5, 6, 2, 3};
        printf("Heights: " + "[array]\n");
        printf("Largest Rectangle Area: " + largestRectangleArea(heights1) + " (Expected: 10)\n");

        int* heights2 = {2, 4};
        printf("\nHeights: " + "[array]\n");
        printf("Largest Rectangle Area: " + largestRectangleArea(heights2) + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Each bar index pushed and popped from stack at most once.
 * Space Complexity: O(N) monotonic stack storage.
 */
