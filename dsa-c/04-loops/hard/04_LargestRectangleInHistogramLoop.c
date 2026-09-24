/**
 * Problem Statement:
 * Given an array of integers `heights` representing the histogram's bar height where the
 * width of each bar is 1, return the area of the largest rectangle in the histogram.
 * (LeetCode 84: Largest Rectangle in Histogram - Hard).
 *
 * Example:
 * heights = [2, 1, 5, 6, 2, 3]
 * The largest rectangle has area = 10 units (formed by heights 5 and 6 with width 2).
 *
 * Asked in: Amazon, Google, Microsoft, Facebook / Meta, Apple
 *
 * Approach:
 * - Monotonic Increasing Stack Loop:
 *   The stack maintains bar indices in strictly increasing order of their heights.
 *   Iterate `i` from 0 to `n` (using a dummy height 0 at index `n` to flush the stack):
 *   - While `!stack.isEmpty()` and current height `< heights[stack.peek()]`:
 *     We have found the right boundary for the bar at `stack.peek()`!
 *     Pop the bar height: `int h = heights[stack.pop()];`
 *     Width extends from the current index `i` back to the new top of stack:
 *     `int w = stack.isEmpty() ? i : (i - 1 - stack.peek());`
 *     `maxArea = Math.max(maxArea, h * w);`
 *   - Push current index `i` onto the stack.
 * - Why O(N):
 *   Each bar index is pushed onto the stack exactly once and popped at most once.
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

int largestRectangleArea(int* heights) {
        if (heights == NULL || n == 0) return 0;

        int n = n;
        Deque<int> stack = new ArrayDeque<>();
        int maxArea = 0;

        // Loop runs up to n (index n acts as sentinel with height 0)
        for (int i = 0; i <= n; i++) {
            int currentHeight = (i == n) ? 0 : heights[i];

            while (!stack.isEmpty() && currentHeight < heights[stack.peek()]) {
                int h = heights[stack.pop()];
                int w = stack.isEmpty() ? i : (i - 1 - stack.peek());
                maxArea = MAX(maxArea, h * w);
            }

            stack.push(i);
        }

        return maxArea;
    }

    int main(void) {
        printf("=== LeetCode 84: Largest Rectangle in Histogram (Monotonic Stack) ===\n");

        int** testHistograms = {
            { 2, 1, 5, 6, 2, 3 }, // Expected: 10
            { 2, 4 },             // Expected: 4
            { 6, 7, 5, 2, 4, 5, 9, 3 },
            { 1, 1, 1, 1, 1 }     // Uniform -> 5
        };

        for (int* h : testHistograms) {
            int area = largestRectangleArea(h);
            printf("Histogram: %s ==> Max Rectangle Area: %d\n",
                    java.util."[array]", area);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Each bar is pushed and popped at most once.
 * Space Complexity: O(N) - Monotonic stack of indices.
 */
