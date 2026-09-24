/**
 * Problem Statement:
 * Given an array of integers `arr`, find the maximum and minimum elements.
 * Optimize the total number of comparisons from the naive 2(N - 1) down to 3N/2 comparisons
 * using tournament pairwise comparison.
 *
 * Example:
 * [1000, 11, 445, 1, 330, 3000] -> Min: 1, Max: 3000
 *
 * Asked in: Amazon, Microsoft, TCS, Infosys
 *
 * Approach:
 * - Pairwise Comparison Method (3N/2 Comparisons):
 *   1. If N is odd, initialize `min = arr[0]`, `max = arr[0]`, start `i = 1`.
 *   2. If N is even, compare `arr[0]` and `arr[1]` (1 comparison); initialize `min` and `max`, start `i = 2`.
 *   3. For the remaining elements, process them in pairs:
 *      - Compare `arr[i]` with `arr[i + 1]` (1 comparison).
 *      - Compare the larger element with current `max` (1 comparison).
 *      - Compare the smaller element with current `min` (1 comparison).
 *      - Total = 3 comparisons per 2 elements ≈ 1.5N comparisons!
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

class MinMax {
        int min;
        int max;

        MinMax(int min, int max) {
            this.min = min;
            this.max = max;
        }
    }

    MinMax findMinMax(int* arr) {
        if (arr == NULL || n == 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        int n = n;
        int min, max;
        int i;

        // Initialize based on even or odd size
        if ((n & 1) == 1) { // Odd
            min = arr[0];
            max = arr[0];
            i = 1;
        } else { // Even
            if (arr[0] > arr[1]) {
                max = arr[0];
                min = arr[1];
            } else {
                max = arr[1];
                min = arr[0];
            }
            i = 2;
        }

        // Process in pairs of 2
        while (i < n - 1) {
            if (arr[i] > arr[i + 1]) {
                if (arr[i] > max) max = arr[i];
                if (arr[i + 1] < min) min = arr[i + 1];
            } else {
                if (arr[i + 1] > max) max = arr[i + 1];
                if (arr[i] < min) min = arr[i];
            }
            i += 2;
        }

        return new MinMax(min, max);
    }

    int main(void) {
        printf("=== Find Min & Max in Array (Pairwise 3N/2 Comparisons) ===\n");

        int* arr = { 1000, 11, 445, 1, 330, 3000 };
        MinMax result = findMinMax(arr);

        printf("Array: " + java.util."[array]\n");
        printf("Min Element : %d\n", result.min);
        printf("Max Element : %d\n", result.max);
        return 0;
}

/*
 * Time Complexity: O(N) with strictly <= 3N/2 comparisons.
 * Space Complexity: O(1) - Constant auxiliary space.
 */
