/*
 * Problem Statement:
 * Implement Counting Sort for non-negative integers:
 * - Non-comparison integer sorting algorithm.
 * - Counts frequency of each distinct value, builds prefix sums to determine
 *   stable output positions.
 * - Time complexity O(N + K) where K is the maximum value in the array.
 * 
 * Asked in: Amazon, Microsoft, Samsung, Uber
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

int* countingSort(int* arr) {
        if (arr == NULL || n <= 1) return arr;

        // Find maximum value
        int max = arr[0];
        for (size_t _idx = 0; _idx < sizeof(arr)/sizeof(arr[0]); _idx++) {
        int val = arr[_idx];
            if (val > max) max = val;
        }

        // 1. Build frequency array
        int* count = (int*)malloc((max + 1) * sizeof(int));
        for (size_t _idx = 0; _idx < sizeof(arr)/sizeof(arr[0]); _idx++) {
        int val = arr[_idx];
            count[val]++;
        }

        // 2. Compute prefix sums (cumulative counts) for stable positioning
        for (int i = 1; i <= max; i++) {
            count[i] += count[i - 1];
        }

        // 3. Build output array in reverse to preserve stability
        int* output = (int*)malloc((n) * sizeof(int));
        for (int i = n - 1; i >= 0; i--) {
            int val = arr[i];
            output[count[val] - 1] = val;
            count[val]--;
        }

        return output;
    }

    int main(void) {
        int* arr = {4, 2, 2, 8, 3, 3, 1};

        printf("Original array: " + "[array]\n");
        int* sorted = countingSort(arr);
        printf("Sorted array:   " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N + K) where N is array length and K is maximum element.
 * Space Complexity: O(N + K) for count and output arrays.
 */
