/**
 * Problem: Average of All Contiguous Subarrays of Size K
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Google, Goldman Sachs
 * 
 * Given an array of integers and an integer K, find the average of all contiguous
 * subarrays of size K and return them as an array.
 * 
 * Approach - Fixed Sliding Window:
 * Keep a running sum of the window.
 * Each iteration: add new right element, remove old left element, compute average.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N - K + 1) for result.
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

double* findAverages(int* arr, int k) {
        int n = n;
        double* result = (double*)malloc((n - k + 1) * sizeof(double));
        double windowSum = 0;

        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        result[0] = windowSum / k;

        for (int i = k; i < n; i++) {
            windowSum += arr[i] - arr[i - k];
            result[i - k + 1] = windowSum / k;
        }

        return result;
    }

    int main(void) {
        int* arr = {1, 3, 2, 6, -1, 4, 1, 8, 2};
        double* avgs = findAverages(arr, 5);
        printf("%s", "Averages of k=5: ");
        for (size_t _idx = 0; _idx < sizeof(avgs)/sizeof(avgs[0]); _idx++) {
        double avg = avgs[_idx];
            printf("%.1f ", avg);
        }
        printf("(Expected: 2.2 2.8 2.4 3.6 2.8)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
