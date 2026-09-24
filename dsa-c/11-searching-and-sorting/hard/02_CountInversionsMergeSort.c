/*
 * Problem Statement:
 * Given an array of integers, find the Inversion Count in the array.
 * Inversion Count indicates how far (or close) the array is from being sorted.
 * Two elements arr[i] and arr[j] form an inversion if arr[i] > arr[j] and i < j.
 * 
 * Example:
 * Input: arr = [8, 4, 2, 1]
 * Output: 6
 * Inversions: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1)
 * 
 * Asked in: Amazon, Microsoft, Flipkart, Google
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
     * Enhanced Merge Sort:
     * While merging two sorted halves arr[low..mid] and arr[mid+1..high]:
     * If arr[i] > arr[j], then since left half is sorted, EVERY element from
     * i to mid is strictly greater than arr[j]!
     * Count += (mid - i + 1).
     */
    long long countInversions(int* arr) {
        if (arr == NULL || n <= 1) return 0;
        int* temp = (int*)malloc((n) * sizeof(int));
        return mergeSortAndCount(arr, 0, n - 1, temp);
    }

    static long long mergeSortAndCount(int* arr, int low, int high, int* temp) {
        long long count = 0;
        if (low < high) {
            int mid = low + (high - low) / 2;
            count += mergeSortAndCount(arr, low, mid, temp);
            count += mergeSortAndCount(arr, mid + 1, high, temp);
            count += mergeAndCount(arr, low, mid, high, temp);
        }
        return count;
    }

    static long long mergeAndCount(int* arr, int low, int mid, int high, int* temp) {
        for (int i = low; i <= high; i++) temp[i] = arr[i];

        int i = low;
        int j = mid + 1;
        int k = low;
        long long invCount = 0;

        while (i <= mid && j <= high) {
            if (temp[i] <= temp[j]) {
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
                invCount += (mid - i + 1); // Key inversion logic
            }
        }

        while (i <= mid) arr[k++] = temp[i++];
        return invCount;
    }

    int main(void) {
        int* arr1 = {8, 4, 2, 1};
        printf("Array: " + "[array]\n");
        printf("Inversion count: " + countInversions(arr1) + " (Expected: 6)\n");

        int* arr2 = {1, 20, 6, 4, 5};
        printf("\nArray: " + "[array]\n");
        printf("Inversion count: " + countInversions(arr2) + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N log N) - Modified MergeSort.
 * Space Complexity: O(N) auxiliary space.
 */
