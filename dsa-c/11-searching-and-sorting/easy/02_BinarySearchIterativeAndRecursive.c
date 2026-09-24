/*
 * Problem Statement:
 * Implement Binary Search in a sorted array using both Iterative and Recursive techniques:
 * - Handle integer overflow safely in midpoint calculation: `low + (high - low) / 2`.
 * - Return index if found, else return -1.
 * 
 * Asked in: Google, Microsoft, Amazon, Facebook/Meta
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

// 1. Iterative Binary Search
    int searchIterative(int* arr, int target) {
        int low = 0;
        int high = n - 1;

        while (low <= high) {
            // Safe midpoint to prevent (low + high) integer overflow
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }

    // 2. Recursive Binary Search
    int searchRecursive(int* arr, int target) {
        return recursiveHelper(arr, target, 0, n - 1);
    }

    static int recursiveHelper(int* arr, int target, int low, int high) {
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return recursiveHelper(arr, target, mid + 1, high);
        } else {
            return recursiveHelper(arr, target, low, mid - 1);
        }
    }

    int main(void) {
        int* sorted = {3, 9, 14, 19, 25, 31, 42, 55, 68, 77, 89, 99};

        printf("Array: " + "[array]\n");
        int* queries = {31, 3, 99, 50};

        printf("--- Binary Search Queries ---\n");
        for (size_t _idx = 0; _idx < sizeof(queries)/sizeof(queries[0]); _idx++) {
        int q = queries[_idx];
            int iterIdx = searchIterative(sorted, q);
            int recIdx = searchRecursive(sorted, q);
            printf("Target: %2d -> Iterative: %2d | Recursive: %2d\n", q, iterIdx, recIdx);
        }
        return 0;
}

/*
 * Time Complexity: O(log N) - Search space halves at every step.
 * Space Complexity: Iterative: O(1) auxiliary space; Recursive: O(log N) stack frames.
 */
