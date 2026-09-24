/*
 * Problem Statement:
 * Given a sorted array where you do not know beforehand whether it is sorted in
 * ascending or descending order, implement an Order-Agnostic Binary Search to find target.
 * 
 * Asked in: Amazon, Goldman Sachs, Cognizant
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
     * Check first element vs last element:
     * If arr[0] <= arr[length - 1], the array is ascending.
     * Otherwise, it is descending.
     * Use the flag to adapt low/high updates.
     */
    int orderAgnosticSearch(int* arr, int target) {
        if (arr == NULL || n == 0) return -1;

        int low = 0;
        int high = n - 1;
        bool isAscending = arr[low] <= arr[high];

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            }

            if (isAscending) {
                if (arr[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else { // Descending order
                if (arr[mid] > target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }

    int main(void) {
        int* asc = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
        int* desc = {91, 72, 56, 38, 23, 16, 12, 8, 5, 2};

        int target = 23;
        printf("Ascending array:  " + "[array]\n");
        printf("Search for %d: Index %d\n", target, orderAgnosticSearch(asc, target));

        printf("\nDescending array: " + "[array]\n");
        printf("Search for %d: Index %d\n", target, orderAgnosticSearch(desc, target));
        return 0;
}

/*
 * Time Complexity: O(log N) binary search steps.
 * Space Complexity: O(1) auxiliary space.
 */
