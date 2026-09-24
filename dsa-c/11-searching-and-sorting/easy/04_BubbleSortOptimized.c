/*
 * Problem Statement:
 * Implement an Optimized Bubble Sort:
 * - Repeatedly step through list, compare adjacent elements, and swap if out of order.
 * - Optimization: Track a `swapped` boolean flag. If an entire pass completes without
 *   any swap, the array is already fully sorted. Break early!
 * - Achieves O(N) best case on already sorted inputs.
 * 
 * Asked in: TCS, Infosys, Capgemini, Wipro
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

void bubbleSort(int* arr) {
        int n = n;

        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;

            // In each pass, the largest remaining element bubbles up to index n - 1 - i
            for (int j = 0; j < n - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }

            // Early exit optimization
            if (!swapped) break;
        }
    }

    int main(void) {
        int* arr1 = {64, 34, 25, 12, 22, 11, 90};
        printf("Original: " + "[array]\n");
        bubbleSort(arr1);
        printf("Sorted:   " + "[array]\n");

        int* alreadySorted = {1, 2, 3, 4, 5};
        bubbleSort(alreadySorted); // Exits after 1 pass
        printf("\nAlready sorted test: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: Best: O(N) when already sorted; Worst & Average: O(N^2).
 * Space Complexity: O(1) in-place sorting.
 */
