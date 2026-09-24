/*
 * Problem Statement:
 * You are given an m x n integer matrix matrix with the following two properties:
 * 1. Each row is sorted in non-decreasing order.
 * 2. The first integer of each row is greater than the last integer of the previous row.
 * Given an integer target, return true if target is in matrix or false otherwise.
 * You must write a solution in O(log(m * n)) time complexity.
 * (LeetCode 74: Search a 2D Matrix)
 * 
 * Example:
 * matrix = [
 *   [1, 3, 5, 7],
 *   [10, 11, 16, 20],
 *   [23, 30, 34, 60]
 * ]
 * target = 3 -> true
 * target = 13 -> false
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple
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
     * Virtual 1D Flattening:
     * - The entire m x n matrix can be viewed as a 1D sorted array of length (m * n).
     * - Virtual index idx maps to 2D coordinates:
     *   row = idx / n
     *   col = idx % n
     * - Standard binary search over range [0, m * n - 1].
     */
    bool searchMatrix(int** matrix, int target) {
        if (matrix == NULL || n == 0 || matrix[0].length == 0) return false;

        int m = n;
        int n = matrix[0].length;
        int low = 0;
        int high = m * n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int midVal = matrix[mid / n][mid % n];

            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

    int main(void) {
        int** matrix = {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 60}
        };

        printf("--- 2D Matrix Binary Search ---\n");
        int* targets = {3, 13, 20, 60, 0, 61};

        for (size_t _idx = 0; _idx < sizeof(targets)/sizeof(targets[0]); _idx++) {
        int t = targets[_idx];
            printf("Target %2d present: %b\n", t, searchMatrix(matrix, t));
        }
        return 0;
}

/*
 * Time Complexity: O(log(M * N)) - Standard binary search over M * N cells.
 * Space Complexity: O(1) auxiliary space.
 */
