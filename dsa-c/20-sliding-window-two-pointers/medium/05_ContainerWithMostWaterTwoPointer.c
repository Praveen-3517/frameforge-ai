/**
 * Problem: Container With Most Water (LeetCode 11)
 * Category: Two Pointers (Opposite Ends) | Medium
 * Asked in: Amazon, Google, Apple, Microsoft, Facebook
 * 
 * You are given an integer array height of length n. There are n vertical lines drawn such that
 * the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container such that the container
 * contains the most water. Return the maximum amount of water a container can store.
 * 
 * Approach - Greedy Two Pointer:
 * Water = min(height[left], height[right]) * (right - left).
 * Move the pointer with the SHORTER height inward (since the shorter side limits capacity).
 * Moving the taller side can only decrease or maintain width without increasing height limit.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int maxArea(int* height) {
        int left = 0;
        int right = n - 1;
        int maxWater = 0;

        while (left < right) {
            int water = MIN(height[left], height[right]) * (right - left);
            maxWater = MAX(maxWater, water);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxWater;
    }

    int main(void) {
        printf("%d (Expected: 49)\n", maxArea((int[]){1, 8, 6, 2, 5, 4, 8, 3, 7}));
        // Lines at index 1 (height=8) and 8 (height=7), width=7, water=7*7=49
        printf("%d (Expected: 1)\n", maxArea((int[]){1, 1}));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
