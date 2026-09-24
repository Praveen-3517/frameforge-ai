/**
 * Problem Statement:
 * Given an array of integers `heights` representing the histogram's bar height where
 * the width of each bar is 1, return the area of the largest rectangle in the histogram.
 * (LeetCode 84: Largest Rectangle in Histogram - Hard).
 *
 * Asked in: Google, Meta, Amazon, Microsoft
 *
 * Approach:
 * - Monotonic Stack / Next & Previous Smaller Element:
 *   For each bar `i`, the largest rectangle with height `heights[i]` extends:
 *   - As far left as possible until a bar with height < `heights[i]` is encountered.
 *   - As far right as possible until a bar with height < `heights[i]` is encountered.
 *   - Using a single monotonic stack pass:
 *     Maintain increasing bar indices.
 *     When a smaller bar arrives at index `i`, pop the top bar `h = heights[stack.pop()]`.
 *     Width = `stack.isEmpty() ? i : (i - stack.peek() - 1)`.
 *     `maxArea = Math.max(maxArea, h * width)`.
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
        printf("=== LeetCode 84: Largest Rectangle in Histogram (Monotonic Stack) ===\n");

        int** testHistograms = {
            { 2, 1, 5, 6, 2, 3 },
            { 2, 4 },
            { 6, 2, 5, 4, 5, 1, 6 }
        };

        for (int* h : testHistograms) {
            int area = largestRectangleArea(h);
            printf("Histogram: %s ==> Max Area: %d\n", "[array]", area);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass where each index is pushed/popped at most once.
 * Space Complexity: O(N) - Monotonic index stack.
 */
