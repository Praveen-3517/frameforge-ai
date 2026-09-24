/*
 * Problem Statement:
 * Implement the Merge Sort algorithm:
 * - Divide array into two halves recursively until base case (length <= 1).
 * - Merge the two sorted subarrays into a single sorted range.
 * - Guarantees O(N log N) time complexity in all cases (Best, Average, Worst).
 * - Stable sorting algorithm.
 * 
 * Asked in: Amazon, Microsoft, Goldman Sachs, Uber
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

void mergeSort(int* arr) {
        if (arr == NULL || n <= 1) return;
        int* temp = (int*)malloc((n) * sizeof(int));
        sort(arr, 0, n - 1, temp);
    }

    static void sort(int* arr, int low, int high, int* temp) {
        if (low >= high) return;

        int mid = low + (high - low) / 2;
        sort(arr, low, mid, temp);
        sort(arr, mid + 1, high, temp);
        merge(arr, low, mid, high, temp);
    }

    static void merge(int* arr, int low, int mid, int high, int* temp) {
        // Copy segment to temp buffer
        for (int i = low; i <= high; i++) {
            temp[i] = arr[i];
        }

        int i = low;
        int j = mid + 1;
        int k = low;

        while (i <= mid && j <= high) {
            if (temp[i] <= temp[j]) { // <= ensures stability
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
            }
        }

        while (i <= mid) {
            arr[k++] = temp[i++];
        }
        // Elements from right half (j..high) already in position
    }

    int main(void) {
        int* arr = {38, 27, 43, 3, 9, 82, 10};

        printf("Original array: " + "[array]\n");
        mergeSort(arr);
        printf("Sorted array:   " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N log N) in all cases (Best, Average, Worst).
 * Space Complexity: O(N) for auxiliary merge buffer + O(log N) stack frames.
 */
