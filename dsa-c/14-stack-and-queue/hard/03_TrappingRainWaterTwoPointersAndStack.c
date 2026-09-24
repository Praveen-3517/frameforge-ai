/*
 * Problem Statement:
 * Given n non-negative integers representing an elevation map where the width of each
 * bar is 1, compute how much water it can trap after raining.
 * Implement both:
 * 1. Monotonic Stack Approach (O(N) time, O(N) space)
 * 2. Two-Pointer Approach (O(N) time, O(1) space)
 * (LeetCode 42: Trapping Rain Water)
 * 
 * Example:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Apple, Microsoft, Bloomberg
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

// Approach 1: Monotonic Stack (Computes trapped water horizontally bounded by troughs)
    int trapStack(int* height) {
        Deque<int> stack = new ArrayDeque<>(); // Stores indices
        int water = 0;

        for (int curr = 0; curr < n; curr++) {
            while (!stack.isEmpty() && height[curr] > height[stack.peek()]) {
                int bottomIdx = stack.pop();
                if (stack.isEmpty()) break;

                int leftIdx = stack.peek();
                int distance = curr - leftIdx - 1;
                int boundedHeight = MIN(height[leftIdx], height[curr]) - height[bottomIdx];
                water += distance * boundedHeight;
            }
            stack.push(curr);
        }

        return water;
    }

    // Approach 2: Two Pointers (O(1) space optimal)
    int trapTwoPointers(int* height) {
        if (height == NULL || n < 3) return 0;

        int left = 0, right = n - 1;
        int leftMax = 0, rightMax = 0;
        int totalWater = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    totalWater += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    totalWater += rightMax - height[right];
                }
                right--;
            }
        }

        return totalWater;
    }

    int main(void) {
        int* height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

        printf("Elevation map: " + "[array]\n");
        printf("Trapped Water (Stack):        " + trapStack(height) + " units (Expected: 6)\n");
        printf("Trapped Water (Two Pointers): " + trapTwoPointers(height) + " units (Expected: 6)\n");
        return 0;
}

/*
 * Time Complexity: O(N) linear time for both approaches.
 * Space Complexity: Stack: O(N); Two Pointers: O(1) auxiliary space.
 */
