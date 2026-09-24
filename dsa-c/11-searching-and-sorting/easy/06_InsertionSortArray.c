/*
 * Problem Statement:
 * Implement Insertion Sort:
 * - Analogous to sorting a hand of playing cards.
 * - For each element at index i, shift elements in sorted sublist arr[0...i-1] that are
 *   greater than arr[i] one position to the right.
 * - Insert key into its correct sorted location.
 * - Highly efficient (O(N) time) for small or nearly-sorted datasets; adaptive and stable.
 * 
 * Asked in: Amazon, Oracle, TCS, IBM
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

void insertionSort(int* arr) {
        int n = n;

        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;

            // Shift elements of arr[0...i-1] that are greater than key to one position ahead
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;
        }
    }

    int main(void) {
        int* arr = {12, 11, 13, 5, 6};

        printf("Original array: " + "[array]\n");
        insertionSort(arr);
        printf("Sorted array:   " + "[array]\n");

        int* nearlySorted = {1, 2, 4, 3, 5, 6};
        insertionSort(nearlySorted);
        printf("Nearly sorted:  " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: Best: O(N) when nearly sorted; Worst & Average: O(N^2).
 * Space Complexity: O(1) in-place sorting.
 */
