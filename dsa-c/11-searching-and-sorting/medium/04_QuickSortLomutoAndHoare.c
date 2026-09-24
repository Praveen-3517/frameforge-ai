/*
 * Problem Statement:
 * Implement QuickSort with both partitioning schemes:
 * 1. Lomuto Partition Scheme (simpler to implement, pivot at end).
 * 2. Hoare Partition Scheme (original scheme by Tony Hoare, fewer swaps on average).
 * 
 * Asked in: Google, Microsoft, Amazon, Oracle, Apple
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

// 1. Lomuto Partition Scheme
    void quickSortLomuto(int* arr, int low, int high) {
        if (low < high) {
            int pIndex = partitionLomuto(arr, low, high);
            quickSortLomuto(arr, low, pIndex - 1);
            quickSortLomuto(arr, pIndex + 1, high);
        }
    }

    static int partitionLomuto(int* arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);
        return i + 1;
    }

    // 2. Hoare Partition Scheme
    void quickSortHoare(int* arr, int low, int high) {
        if (low < high) {
            int pIndex = partitionHoare(arr, low, high);
            quickSortHoare(arr, low, pIndex);
            quickSortHoare(arr, pIndex + 1, high);
        }
    }

    static int partitionHoare(int* arr, int low, int high) {
        int pivot = arr[low + (high - low) / 2];
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do { i++; } while (arr[i] < pivot);
            do { j--; } while (arr[j] > pivot);

            if (i >= j) return j;
            swap(arr, i, j);
        }
    }

    static void swap(int* arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    int main(void) {
        int* arr1 = {10, 80, 30, 90, 40, 50, 70};
        printf("Original: " + "[array]\n");
        quickSortLomuto(arr1, 0, n - 1);
        printf("Sorted (Lomuto): " + "[array]\n");

        int* arr2 = {10, 80, 30, 90, 40, 50, 70};
        quickSortHoare(arr2, 0, n - 1);
        printf("Sorted (Hoare):  " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: Average & Best: O(N log N); Worst: O(N^2) when array is unbalanced.
 * Space Complexity: O(log N) recursion stack depth on average.
 */
