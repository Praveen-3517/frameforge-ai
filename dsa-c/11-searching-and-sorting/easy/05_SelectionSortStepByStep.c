/*
 * Problem Statement:
 * Implement Selection Sort with step-by-step state logging:
 * - Divide array into sorted prefix and unsorted suffix.
 * - In each pass, scan unsorted suffix to locate minimum element.
 * - Swap minimum element with the first element of unsorted suffix.
 * - Note: Selection sort makes at most N - 1 swaps (ideal when write operations are expensive).
 * 
 * Asked in: Accenture, Cognizant, Wipro
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

void selectionSort(int* arr) {
        int n = n;

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;

            // Find index of minimum element in unsorted range [i, n-1]
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }

            // Swap if minIdx changed
            if (minIdx != i) {
                int temp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = temp;
            }

            printf("Pass %d (min=%2d): %s\n", i + 1, arr[i], "[array]");
        }
    }

    int main(void) {
        int* arr = {29, 10, 14, 37, 13};

        printf("Initial array: " + "[array]\n");
        printf("--- Executing Selection Sort ---\n");
        selectionSort(arr);
        printf("Final sorted:  " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N^2) in best, average, and worst cases (always scans entire unsorted suffix).
 * Space Complexity: O(1) in-place sorting.
 */
