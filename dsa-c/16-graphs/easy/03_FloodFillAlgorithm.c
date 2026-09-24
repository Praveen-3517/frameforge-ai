/**
 * Problem: Flood Fill (LeetCode 733)
 * Asked in: Amazon, Google, Microsoft, Uber
 * 
 * An image is represented by an m x n integer grid image where image[i][j] represents
 * the pixel value of the image. Perform flood fill from (sr, sc) with color newColor.
 * 
 * Approach:
 * Recursive DFS:
 * 1. Record original color = image[sr][sc].
 * 2. If original color == newColor, return image immediately (avoid infinite recursion).
 * 3. Change current pixel to newColor.
 * 4. Recurse in 4 cardinal directions (up, down, left, right) if neighboring pixel
 *    matches original color.
 * 
 * Time Complexity: O(M * N) in worst case visiting all pixels.
 * Space Complexity: O(M * N) recursion stack.
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

int** floodFill(int** image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        if (originalColor != color) {
            dfs(image, sr, sc, originalColor, color);
        }
        return image;
    }

    static void dfs(int** image, int r, int c, int origColor, int newColor) {
        if (r < 0 || r >= n || c < 0 || c >= image[0].length || image[r][c] != origColor) {
            return;
        }

        image[r][c] = newColor;

        dfs(image, r + 1, c, origColor, newColor);
        dfs(image, r - 1, c, origColor, newColor);
        dfs(image, r, c + 1, origColor, newColor);
        dfs(image, r, c - 1, origColor, newColor);
    }

    int main(void) {
        int** image = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };

        int** result = floodFill(image, 1, 1, 2);
        printf("Flood Fill Result:\n");
        for (int* row : result) {
            printf("[array]\n");
        }
        // Expected:
        // [2, 2, 2]
        // [2, 2, 0]
        // [2, 0, 1]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
