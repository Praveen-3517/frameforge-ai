/**
 * Problem: Pascal's Triangle (LeetCode 118)
 * Asked in: Amazon, Apple, Goldman Sachs
 * 
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 * 
 * Approach:
 * 2D DP construction:
 * Each row starts and ends with 1.
 * For 1 <= j < i: row[j] = prevRow[j - 1] + prevRow[j].
 * 
 * Time Complexity: O(numRows^2)
 * Space Complexity: O(numRows^2) for the output triangle.
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

int*> generate(int numRows) {
        int*> triangle = new ArrayList<>(numRows);

        for (int i = 0; i < numRows; i++) {
            int* row = new ArrayList<>(i + 1);
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    row.add(1);
                } else {
                    int* prevRow = triangle.get(i - 1);
                    row.add(prevRow.get(j - 1) + prevRow.get(j));
                }
            }
            triangle.add(row);
        }

        return triangle;
    }

    int main(void) {
        int*> result = generate(5);
        printf("Pascal's Triangle (5 rows): %d\n", result);
        // Expected: [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
