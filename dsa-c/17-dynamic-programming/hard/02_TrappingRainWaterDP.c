/**
 * Problem: Trapping Rain Water (LeetCode 42 - DP Solution)
 * Asked in: Amazon, Google, Microsoft, Bloomberg, Apple
 * 
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * Approach:
 * Prefix and Suffix Max DP Arrays:
 * Water trapped at bar i is determined by:
 *   water[i] = max(0, min(maxLeft[i], maxRight[i]) - height[i])
 * 1. Precompute maxLeft array where maxLeft[i] is maximum height in height[0..i].
 * 2. Precompute maxRight array where maxRight[i] is maximum height in height[i..n-1].
 * 3. Sum water trapped across all indices.
 * 
 * Time Complexity: O(N) with three linear passes.
 * Space Complexity: O(N) for DP arrays.
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

int trap(int* height) {
        if (height == NULL || n <= 2) return 0;

        int n = n;
        int* leftMax = (int*)malloc((n) * sizeof(int));
        int* rightMax = (int*)malloc((n) * sizeof(int));

        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = MAX(leftMax[i - 1], height[i]);
        }

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = MAX(rightMax[i + 1], height[i]);
        }

        int totalWater = 0;
        for (int i = 0; i < n; i++) {
            totalWater += MIN(leftMax[i], rightMax[i]) - height[i];
        }

        return totalWater;
    }

    int main(void) {
        int* height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        printf("Trapped water 1: " + trap(height1) + " (Expected: 6)\n");

        int* height2 = {4, 2, 0, 3, 2, 5};
        printf("Trapped water 2: " + trap(height2) + " (Expected: 9)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
